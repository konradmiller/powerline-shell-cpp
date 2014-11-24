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

	void inverse();

	std::string getColorCode() const;

	Color* getForegroundColor();
	Color* getBackgroundColor();

	static std::string resetColor()
	{
		return special( "esc" ) + "[0m";
	}

	static std::string resetForegroundColor()
	{
		return special( "esc" ) + "[39m";
	}

	static std::string resetBackgroundColor()
	{
		return special( "esc" ) + "[49m";
	}

private:
	Color	*foreground,
		*background;
};


std::ostream& operator<<( std::ostream& os, const ColorCombination& c );

#endif
