#ifndef COLOR_CODE_H__
#define COLOR_CODE_H__

#include <cassert>
#include <map>
#include <string>
#include <sstream>

#include "special_character.h"

// 256color terminals have value [0, 5] per RGB channel
// or 0-24 gray scale shades
class Color
{
public:
	Color()
		: red(0), green(0), blue(0), color(true)
	{}

	Color( const unsigned short r, const unsigned short g, const unsigned short b )
		: red(r), green(g), blue(b), color(true)
	{
		assert( red   <= 5 );
		assert( green <= 5 );
		assert( blue  <= 5 );
	}

	Color( unsigned short g )
		: gray(g), color(false)
	{
		assert( gray <= 0x17 );
	}

	int value() const
	{
		if( color )
			return 16 + 36*red + 6*green + blue;
		else
			return 0xe8 + gray;
	}

private:
	unsigned short red, green, blue;
	unsigned short gray;
	bool color;
};


class ColorCombination
{
public:
	ColorCombination( Color fg, Color bg )
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
	Color	foreground,
		background;
};


std::ostream& operator<<( std::ostream& os, const ColorCombination& c );

#endif
