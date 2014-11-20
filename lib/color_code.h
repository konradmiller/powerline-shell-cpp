#ifndef COLOR_CODE_H__
#define COLOR_CODE_H__

#include <map>
#include <string>
#include <sstream>

#include "special_character.h"


typedef std::map< std::string, std::string > ColorMapping;


enum Color
{
	BLACK = 0, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE, NONE = 9
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


private:
	static ColorMapping colors;

	// make sure that this singleton is not copied
	ColorCode() {};
	ColorCode( ColorCode const& );
	void operator=( ColorCode const& );
};



#endif
