#ifndef COLOR_CODE_H__
#define COLOR_CODE_H__

#include <cassert>
#include <map>
#include <string>
#include <sstream>

#include "special_character.h"


typedef std::map< std::string, std::string > ColorMapping;


enum Color
{
	BLACK = 0, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE, NONE = 9
};


// 256color terminals have 6-Bit per RGB channel
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

enum ColorVariant
{
	REGULAR   = 0, BOLD = 1, UNDERLINE = 4
};


// resetColor is setColor with default values
#define resetColor setColor
std::string setColor( Color = NONE, Color = NONE, bool = false, ColorVariant = REGULAR );


class ColorCode
{
public:
	static std::string
	getBasicColorCode( Color foreground = NONE, Color background = NONE, bool bright = false, ColorVariant variant = REGULAR )
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

	static std::string EnumarateBasicColors()
	{
		std::stringstream rainbow;
		for( int bright = 0; bright <= 1; ++bright )
		{
			for( unsigned bg = (unsigned) BLACK; bg <= (unsigned) WHITE; ++bg )
			{
				for( unsigned fg = (unsigned) BLACK; fg <= (unsigned) WHITE; ++fg )
					rainbow << getBasicColorCode( (Color) fg, (Color) bg, bright ) << " x ";
				rainbow << resetColor() << std::endl;
			}
			rainbow << resetColor() << std::endl << std::endl;
		}
		return rainbow.str();
	}

	static std::string get256ColorCode( const Color256& foreground, const Color256& background )
	{
		std::stringstream code;
		code	<< special( "esc" )	<< "[38;5;"
			<< foreground.value()	<< "m";
		code	<< special( "esc" )	<< "[48;5;"
			<< background.value()	<< "m";
		return code.str();
	}

	static std::string Enumerate256Colors()
	{
		std::stringstream rainbow;
		for( unsigned short r = 0; r < 6; ++r )
		{
			for( unsigned short g = 0; g < 6; ++g )
			{
				for( unsigned short b = 0; b < 6; ++b )
					rainbow << get256ColorCode( Color256(r,g,b), Color256(r,g,b) ) << " x ";
			}
			rainbow << resetColor() << std::endl;
		}
		rainbow << resetColor() << std::endl << std::endl;

		for( unsigned short r = 0; r < 6; ++r )
			rainbow << get256ColorCode( Color256(r,0,0), Color256(r,0,0) ) << " x ";

		for( unsigned short g = 0; g < 6; ++g )
			rainbow << get256ColorCode( Color256(0,g,0), Color256(0,g,0) ) << " x ";
		
		for( unsigned short b = 0; b < 6; ++b )
			rainbow << get256ColorCode( Color256(0,0,b), Color256(0,0,b) ) << " x ";

		rainbow << resetColor() << std::endl << std::endl;

		return rainbow.str();
	}


private:
	static ColorMapping colors;

	// make sure that this singleton is not copied
	ColorCode() {};
	ColorCode( ColorCode const& );
	void operator=( ColorCode const& );
};



#endif
