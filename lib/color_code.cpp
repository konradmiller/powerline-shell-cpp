#include "color_code.h"

namespace ColorCode
{
	std::string
	resetColor()
	{
		return getBasicColorCode();
	}

	std::string
	getBasicColorCode( Color foreground, Color background, bool bright, ColorVariant variant )
	{
		int foreground_summand = bright ? 90  : 30;
		int background_summand = bright ? 100 : 40;

		std::stringstream code;
		code	<< special( "esc" )                 << "["
			<< variant                          << ";"
			<< foreground_summand + foreground  << ";"
			<< background_summand + background  << "m";
		return code.str();
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
