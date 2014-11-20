#include <unistd.h>
#include <sys/param.h>

#include "cwd.h"

namespace cwd
{
	std::string getSegment()
	{
		char cpath[MAXPATHLEN];
		getcwd( cpath, sizeof(cpath)/sizeof(char) );
		std::string path = cpath;
		
		return path;
	}
}

