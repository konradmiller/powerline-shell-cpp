#include <unistd.h>
#include <sys/param.h>

#include "special_character.h"
#include "string_manipulation.h"
#include "cwd.h"

namespace cwd
{
	std::string getSegment()
	{
		char cpath[MAXPATHLEN];
		getcwd( cpath, sizeof(cpath)/sizeof(char) );
		std::string path = cpath;

		//path = replaceFirstSubstring( path, "/", special("separator") );
		path = replaceAllSubstrings( path, "/", "#" );
		
		return path;
	}
}

