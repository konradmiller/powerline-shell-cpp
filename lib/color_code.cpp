#include <ostream>
#include "color_code.h"

std::string ColorCombination::getColorCode() const
{
	std::stringstream code;
	code	<< special( "esc" )	<< "[38;5;"
		<< foreground.value()	<< "m";
	code	<< special( "esc" )	<< "[48;5;"
		<< background.value()	<< "m";
	return code.str();
}


void ColorCombination::inverse()
{
	Color tmp	= foreground;
	foreground	= background;
	background	= tmp;
}


std::ostream& operator<<( std::ostream& os, const ColorCombination& c )
{
	os << c.getColorCode();
	return os;
}
