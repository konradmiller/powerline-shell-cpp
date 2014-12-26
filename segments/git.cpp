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
  class GitRepoStateSnapshot {

  public:
    GitRepoStateSnapshot(std::string &repoPath);
    ~GitRepoStateSnapshot() {
      git_reference_free(currentBranchHandle);
      git_repository_free(repoHandle);
    }

    std::string getBranchName() const { return currentBranchName; }
    int getNumGenerationsAhead() const { return numCommitsAhead; }
    int getNumGenerationsBehind() const { return numCommitsBehind; }
    bool repoIsClean() const { return repoClean; }
    bool repoContainsUntrackedFiles() const {return containsUntrackedFiles; }
    bool isGitRepo() const { return gitRepoFound; }

  private:
    git_reference *currentBranchHandle;
    git_repository *repoHandle;
  
    size_t numCommitsAhead, numCommitsBehind;
    std::string currentBranchName;
    bool repoClean;
    bool containsUntrackedFiles;
    bool gitRepoFound;

    void openGitRepo(std::string &repoPath);
    void computeCurrentBranchName();
    void computeGenerationDelta();
    void computeRepoClean();

    git_commit *branchToCommit(git_reference *branch);
  };

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
    const char *branch_name;

    if (git_repository_head_detached(repoHandle)) {
      currentBranchHandle = nullptr;
      currentBranchName = "(detached head)";
      return;
    }

    if (git_repository_head_unborn(repoHandle)) {
      currentBranchHandle = nullptr;
      currentBranchName = "(no branch)";
      return;
    }

    git_repository_head(&currentBranchHandle, repoHandle);

    git_branch_name(&branch_name, currentBranchHandle);
    currentBranchName = branch_name;
  }

  void GitRepoStateSnapshot::computeGenerationDelta() {
    if (!currentBranchHandle) //detached head
      return;

    git_commit *localHead, *upstreamHead;

    git_reference *upstream;
    git_branch_upstream(&upstream, currentBranchHandle);
    
    localHead = branchToCommit(currentBranchHandle);
    upstreamHead = branchToCommit(upstream);

    const git_oid *localOid, *upstreamOid;
    localOid = git_commit_id(localHead);
    upstreamOid = git_commit_id(upstreamHead);

    // for some reason, a commit to the local repo is a commit *behind* for this function
    // TODO: More testing to make sure this works as intended
    git_graph_ahead_behind(&numCommitsBehind, &numCommitsAhead, repoHandle, localOid, upstreamOid);

    git_commit_free(localHead);
    git_commit_free(upstreamHead);
    git_reference_free(upstream);
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

  void GitRepoStateSnapshot::computeRepoClean() {
    git_diff *diff;
    git_diff_options opts;
    git_diff_options_init(&opts, GIT_DIFF_OPTIONS_VERSION);
    opts.flags = GIT_DIFF_INCLUDE_UNTRACKED | GIT_DIFF_INCLUDE_TYPECHANGE;

    git_diff_index_to_workdir(&diff, repoHandle, nullptr, &opts);

    int modifiedCount = git_diff_num_deltas(diff);
    int untrackedCount = git_diff_num_deltas_of_type(diff, GIT_DELTA_UNTRACKED);

    containsUntrackedFiles = (untrackedCount > 0);
    repoClean = (modifiedCount == untrackedCount);

    git_diff_free(diff);
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

      if (!repoState.repoIsClean())
	returnString->append("M ");
      
      returnString->append(special("git_branch"));
      returnString->push_back(' ');

      returnString->append(repoState.getBranchName());
      
      if (repoState.getNumGenerationsAhead() > 0) {
	returnString->push_back(' ');
	returnString->append(std::to_string(repoState.getNumGenerationsAhead()));
	returnString->append(special("git_ahead"));
      }
      if (repoState.getNumGenerationsBehind() > 0) {
	returnString->push_back(' ');
	returnString->append(std::to_string(repoState.getNumGenerationsBehind()));
	returnString->append(special("git_behind"));
      }

      if (repoState.repoContainsUntrackedFiles())
	returnString->append(" +");

      return *returnString;
    }
    else
      return std::string();
  }
}

