#include "test_color.h"
#include "color_code.h"

std::string EnumerateColors()
{
	std::stringstream rainbow;
	for( unsigned short r = 0; r < 6; ++r )
	{
		for( unsigned short g = 0; g < 6; ++g )
		{
			for( unsigned short b = 0; b < 6; ++b )
				rainbow << ColorCombination( Color(r,g,b), Color(r,g,b) ) << " x ";
		}
		rainbow << ColorCombination::resetColor() << std::endl;
	}
	rainbow << ColorCombination::resetColor() << std::endl << std::endl;

	for( unsigned short r = 0; r < 6; ++r )
		rainbow << ColorCombination( Color(r,0,0), Color(r,0,0) ) << " x ";

	for( unsigned short g = 0; g < 6; ++g )
		rainbow << ColorCombination( Color(0,g,0), Color(0,g,0) ) << " x ";
	
	for( unsigned short b = 0; b < 6; ++b )
		rainbow << ColorCombination( Color(0,0,b), Color(0,0,b) ) << " x ";

	rainbow << ColorCombination::resetColor() << std::endl << std::endl;

	return rainbow.str();
}


std::string EnumerateGrayscale()
{
	std::stringstream rainbow;
	for( unsigned short g = 0; g < 24; ++g )
		rainbow << ColorCombination( Color(g), Color(g) ) << " x ";

	rainbow << ColorCombination::resetColor() << std::endl << std::endl;
	
	return rainbow.str();
}
