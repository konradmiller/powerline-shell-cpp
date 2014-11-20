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


// resetColor is setColor with default values
#define resetColor setColor
std::string setColor( Color = NONE, Color = NONE );


class ColorCode
{
public:
	static std::string getColorCode( Color foreground, Color background )
	{
		std::stringstream code;

		code	<< special( "esc" )
			<< 30 + foreground
			<< ";"
			<< 40 + background
			<< "m";

		return code.str();
	}
	
	static std::string EnumarateBasicColors()
	{
		std::stringstream rainbow;
		for( unsigned bg = (unsigned) BLACK; bg <= (unsigned) WHITE; ++bg )
		{
			for( unsigned fg = (unsigned) BLACK; fg <= (unsigned) WHITE; ++fg )
				rainbow << getColorCode( (Color) fg, (Color) bg ) << " x ";
			rainbow << resetColor() << std::endl;
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
