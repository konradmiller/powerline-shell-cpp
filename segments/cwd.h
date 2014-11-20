#ifndef CWD_H__
#define CWD_H__

#include <unistd.h>

class Cwd
{
public:
	static std::string getSegment()
	{
		char* cpath = get_current_dir_name();
		std::string path = cpath;
		free( cpath );
		
		return path;
	}
};

#endif
