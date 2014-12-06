#include <unistd.h>
#include <sys/param.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <git2.h>

#include "color_code.h"
#include "special_character.h"
#include "string_manipulation.h"

#include "git.h"

namespace git
{
  typedef std::vector<git_commit *> CommitVector;

  class GitRepoStateSnapshot {

  public:
    GitRepoStateSnapshot(std::string &repoPath);
    GitRepoStateSnapshot() : 
      numGenerationsAheadOrBehind(0), 
      currentBranchName(), 
      localIsAhead(true), 
      repoClean(true),
      gitRepoFound(false) { }

    std::string getBranchName() { return currentBranchName; }
    int getNumGenerationsAheadOrBehind() { return numGenerationsAheadOrBehind; }
    bool isLocalAhead() { return localIsAhead; }
    bool isRepoClean() { return repoClean; }
    bool isGitRepo() { return gitRepoFound; }

  private:
    git_reference *currentBranchHandle;
    git_repository *repoHandle;
  
    int numGenerationsAheadOrBehind;
    std::string currentBranchName;
    bool localIsAhead;
    bool repoClean;
    bool gitRepoFound;

    void openGitRepo(std::string &repoPath);
    void computeCurrentBranchName();
    void computeGenerationDelta();
    void computeRepoClean();
    CommitVector *makeParentsVector(CommitVector *commits);
    void freeCommitVector(CommitVector *commits);

    git_commit *branchToCommit(git_reference *branch);
  };

  git_commit *localHead, *upstreamHead;

  GitRepoStateSnapshot::GitRepoStateSnapshot(std::string &repoPath) {
    openGitRepo(repoPath);
    if (gitRepoFound) {
      computeCurrentBranchName();
      computeGenerationDelta();
      computeRepoClean();
    }
  }

  void GitRepoStateSnapshot::openGitRepo(std::string &repoPath) {
    int error = 0;
    while (repoPath.length() > 1) {
      error = git_repository_open(&repoHandle, repoPath.c_str());
      if (error >= 0) {
	gitRepoFound = true;
	return;
      }
      repoPath.erase(repoPath.rfind("/"));
    }
  }

  void GitRepoStateSnapshot::computeCurrentBranchName() {
    int error = 0;
    git_branch_iterator *it;
    git_branch_t type;
    const char *branch_name;
    
    error = git_branch_iterator_new(&it, repoHandle, GIT_BRANCH_LOCAL);
    if (error) {
      currentBranchName = "(error)";
      return;
    }
    
    do {
      error = git_branch_next(&currentBranchHandle, &type, it);
      if (error == GIT_ITEROVER) { //Head not on branch
	currentBranchName = "(no branch)";
	currentBranchHandle = nullptr;
	git_branch_iterator_free(it);
	return;
      }
    } while (!git_branch_is_head(currentBranchHandle));

    git_branch_name(&branch_name, currentBranchHandle);
    currentBranchName = branch_name;
  }

  static bool operator==(git_oid a, git_oid b) {
    int i;
    for (i = 0; i < GIT_OID_RAWSZ; ++i) {
      if (a.id[i] != b.id[i])
	return false;
    } 
    return true;
  }

  static bool isUpstreamHead(git_commit *c) {
    return (*git_commit_id(c) == *git_commit_id(upstreamHead));
  }

  static bool isLocalHead(git_commit *c) {
    return git_commit_id(c) == git_commit_id(localHead);
  }

  void GitRepoStateSnapshot::computeGenerationDelta() {
    if (!currentBranchHandle) //detached head
      return;

    git_reference *upstream;
    git_branch_upstream(&upstream, currentBranchHandle);
    
    localHead = branchToCommit(currentBranchHandle);
    upstreamHead = branchToCommit(upstream);

    if (git_commit_id(localHead) == git_commit_id(upstreamHead)) {
      localIsAhead = true;
      numGenerationsAheadOrBehind = 0;
      return;
    }

    CommitVector *localCommits, *upstreamCommits, *tmp;
    CommitVector::iterator it; 
    unsigned int generations;
      
    localCommits = new CommitVector();
    localCommits->push_back(localHead);

    upstreamCommits = new CommitVector();
    upstreamCommits->push_back(upstreamHead);

    for (generations = 1; /*forever*/ ; ++generations) {
      
      tmp = makeParentsVector(localCommits);
      freeCommitVector(localCommits);
      localCommits = tmp;

      it = std::find_if(localCommits->begin(), localCommits->end(), isUpstreamHead);
      if (it != localCommits->end()) {
	numGenerationsAheadOrBehind = generations;
	localIsAhead = true;
	break;
      }
    
      tmp = makeParentsVector(upstreamCommits);
      freeCommitVector(upstreamCommits);
      upstreamCommits = tmp;

      it = std::find_if(upstreamCommits->begin(), upstreamCommits->end(), isLocalHead);
      if (it != upstreamCommits->end()) {
	numGenerationsAheadOrBehind = generations;
	localIsAhead = false;
	break;
      }
      
    }
  }

  git_commit *GitRepoStateSnapshot::branchToCommit(git_reference *branch) {
    int error = 0;
    
    git_object *commit_obj;
    error = git_reference_peel(&commit_obj, branch, GIT_OBJ_COMMIT);
    if (error) 
      return nullptr;

    const git_oid *oid = git_object_id(commit_obj);
    
    git_commit *commit;
    error = git_commit_lookup(&commit, repoHandle, oid);
    git_object_free(commit_obj);
    if (error)
      return nullptr;

    return commit;
  }

  CommitVector *GitRepoStateSnapshot::makeParentsVector(CommitVector *commits) {
    int parentCount;
    git_commit *out;
    int i, err;
    CommitVector *parentVector = new CommitVector();
    
    for (git_commit *commit : *commits) {
       
      parentCount = git_commit_parentcount(commit);
      for (i = 0; i < parentCount; ++i) {

	err = git_commit_parent(&out, commit, i);
	if (err)
	  break; 
	  // incomplete parents list => possibly no commit delta found. 
	  // However, this only happens on horribly broken repos

	parentVector->push_back(out);
      }
    }

    return parentVector;
  }

  void GitRepoStateSnapshot::freeCommitVector(CommitVector *commits) {
    for (git_commit *commit : *commits)
      git_commit_free(commit);

    delete commits;
  }

  void GitRepoStateSnapshot::computeRepoClean() {

  }

  std::string getSegment()
  {
    char cpath[MAXPATHLEN];
    if( getcwd(cpath, sizeof(cpath)/sizeof(char)) == NULL )
      return std::string();

    std::string path = cpath;

    GitRepoStateSnapshot repoState(path);
    if (repoState.isGitRepo()) {
      std::string *returnString = new std::string();
      returnString->append(repoState.getBranchName());
      if (repoState.getNumGenerationsAheadOrBehind() > 0) {
	returnString->push_back(' ');
	returnString->append(std::to_string(repoState.getNumGenerationsAheadOrBehind()));
	returnString->push_back(repoState.isLocalAhead() ? '+' : '-');
      }
      return *returnString;
    }
    else
      return std::string();
  }
}

