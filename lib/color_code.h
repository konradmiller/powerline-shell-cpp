#ifndef COLOR_CODE_H__
#define COLOR_CODE_H__

#include <cassert>
#include <map>
#include <string>
#include <sstream>

#include "special_character.h"

// 256color terminals have value [0, 5] per RGB channel
struct Color256
{
	unsigned short _r, _g, _b;

	Color256()
		: _r(0), _g(0), _b(0)
	{}

	Color256( unsigned short r, unsigned short g, unsigned short b )
		: _r(r), _g(g), _b(b)
	{}

	int value() const
	{
		assert( (_r >= 0) && (_r <= 5) );
		assert( (_g >= 0) && (_g <= 5) );
		assert( (_b >= 0) && (_b <= 5) );
		return 16 + 36*_r + 6*_g + _b;
	}
};

class ColorCombination
{
public:
	ColorCombination( Color256 fg, Color256 bg )
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
	Color256 foreground,
		 background;
};


std::ostream& operator<<( std::ostream& os, const ColorCombination& c );

#endif
