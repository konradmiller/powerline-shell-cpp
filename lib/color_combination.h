#ifndef COLOR_COMBINATION_H__
#define COLOR_COMBINATION_H__

#include <cassert>
#include <map>
#include <string>
#include <sstream>
#include <ostream>

#include "color_code.h"
#include "special_character.h"


class ColorCombination
{
public:
	ColorCombination( Color* const fg, Color* const bg )
		: foreground(fg)
		, background(bg)
	{}

	std::string getColorCode() const;
	void inverse();

	static std::string resetColor()
	{
		return special( "esc" ) + "[0m";
	}

private:
	Color	*foreground,
		*background;
};


std::ostream& operator<<( std::ostream& os, const ColorCombination& c );

#endif
