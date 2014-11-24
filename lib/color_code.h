#ifndef COLOR_CODE_H__
#define COLOR_CODE_H__

#include <cassert>
#include <map>
#include <string>
#include <sstream>

#include "special_character.h"

class Color
{
public:
	virtual int value() const = 0;
};


// 256color terminals have value [0, 5] per RGB channel
class Color256 : public Color
{
public:
	Color256() : red(0), green(0), blue(0) {}

	Color256( const unsigned short r, const unsigned short g, const unsigned short b )
		: red(r), green(g), blue(b)
	{
		assert( red   <= 5 );
		assert( green <= 5 );
		assert( blue  <= 5 );
	}

	int value() const;

private:
	unsigned short red, green, blue;
};


// or 0-24 gray scale shades
class GrayScale : public Color
{
public:
	GrayScale() : gray(0) {}

	GrayScale( unsigned short g )
		: gray(g)
	{
		assert( gray <= 0x17 );
	}

	int value() const;

private:
	unsigned short gray;
};


#endif
