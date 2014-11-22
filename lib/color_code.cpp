#include "color_code.h"

namespace ColorCode
{
	std::string
	resetColor()
	{
		return special( "esc" ) + "[0m";
	}

	std::string
	get256ColorCode( const Color256& foreground, const Color256& background )
	{
		std::stringstream code;
		code	<< special( "esc" )	<< "[38;5;"
			<< foreground.value()	<< "m";
		code	<< special( "esc" )	<< "[48;5;"
			<< background.value()	<< "m";
		return code.str();
	}
}
