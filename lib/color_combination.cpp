#include <ostream>

#include "color_code.h"
#include "color_combination.h"
#include "special_character.h"

std::string ColorCombination::getColorCode() const
{
	std::stringstream code;
	if( foreground )
		code << special( "esc" ) << "[38;5;" << foreground->value() << "m";
	else
		code << resetForegroundColor();
		
	if( background )
		code << special( "esc" ) << "[48;5;" << background->value() << "m";
	else
		code << resetBackgroundColor();

	return code.str();
}


void ColorCombination::inverse()
{
	Color *tmp	= foreground;
	foreground	= background;
	background	= tmp;
}


Color* ColorCombination::getForegroundColor()
{
	return foreground;
}

Color* ColorCombination::getBackgroundColor()
{
	return background;
}


std::ostream& operator<<( std::ostream& os, const ColorCombination& c )
{
	os << c.getColorCode();
	return os;
}
