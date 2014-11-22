#include "test_color.h"
#include "color_code.h"

namespace CC = ColorCode;

std::string EnumarateBasicColors()
{
	std::stringstream rainbow;
	for( int bright = 0; bright <= 1; ++bright )
	{
		for( unsigned bg = (unsigned) CC::BLACK; bg <= (unsigned) CC::WHITE; ++bg )
		{
			for( unsigned fg = (unsigned) CC::BLACK; fg <= (unsigned) CC::WHITE; ++fg )
				rainbow << CC::getBasicColorCode( (CC::Color) fg, (CC::Color) bg, bright ) << " x ";
			rainbow << CC::resetColor() << std::endl;
		}
		rainbow << CC::resetColor() << std::endl << std::endl;
	}
	return rainbow.str();
}


std::string Enumerate256Colors()
{
	std::stringstream rainbow;
	for( unsigned short r = 0; r < 6; ++r )
	{
		for( unsigned short g = 0; g < 6; ++g )
		{
			for( unsigned short b = 0; b < 6; ++b )
				rainbow << CC::get256ColorCode( CC::Color256(r,g,b), CC::Color256(r,g,b) ) << " x ";
		}
		rainbow << CC::resetColor() << std::endl;
	}
	rainbow << CC::resetColor() << std::endl << std::endl;

	for( unsigned short r = 0; r < 6; ++r )
		rainbow << CC::get256ColorCode( CC::Color256(r,0,0), CC::Color256(r,0,0) ) << " x ";

	for( unsigned short g = 0; g < 6; ++g )
		rainbow << CC::get256ColorCode( CC::Color256(0,g,0), CC::Color256(0,g,0) ) << " x ";
	
	for( unsigned short b = 0; b < 6; ++b )
		rainbow << CC::get256ColorCode( CC::Color256(0,0,b), CC::Color256(0,0,b) ) << " x ";

	rainbow << CC::resetColor() << std::endl << std::endl;

	return rainbow.str();
}


