#include <unistd.h>
#include <sys/param.h>

#include "color_code.h"
#include "special_character.h"
#include "string_manipulation.h"

#include "cwd.h"

namespace cwd
{
	std::string getSegment()
	{
		char cpath[MAXPATHLEN];
		if( getcwd(cpath, sizeof(cpath)/sizeof(char)) == NULL )
			return std::string();

		std::string path = cpath;

		if( (path.length() > 1) && (path[0] == '/') )
			path = path.substr( 1 );

		path = replaceAllSubstrings( path, "/",
				" " + special("separator_thin") + " " );

		return path;
	}
}

