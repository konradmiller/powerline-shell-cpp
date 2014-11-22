#include <unistd.h>
#include <sys/param.h>

#include "special_character.h"
#include "string_manipulation.h"
#include "cwd.h"

namespace cwd
{
	std::string getSegment( std::string color )
	{
		(void) color;
		char cpath[MAXPATHLEN];
		getcwd( cpath, sizeof(cpath)/sizeof(char) );
		std::string path = cpath;

		if( (path.length() > 1) && (path[0] == '/') )
			path[0] = ' ';

		path = replaceAllSubstrings( path, "/",
				" " + special("separator_thin") + " " );

		return path;
	}
}

