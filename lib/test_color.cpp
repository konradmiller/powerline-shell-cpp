#include "test_color.h"

#include "color_code.h"
#include "color_combination.h"

std::string EnumerateColors()
{
	std::stringstream rainbow;

	// legend for green boxes
	for( unsigned short g = 0; g < 6; ++g )
		rainbow << "          green = " << g << "        ";
	rainbow << std::endl << std::endl;

	// legend for blue values
	rainbow << "   blue = ";
	for( unsigned short g = 0; g < 6; ++g )
	{
		for( unsigned short b = 0; b < 6; ++b )
			rainbow << " " << b << "  ";
		rainbow << "   ";
	}
	rainbow << std::endl << std::endl;
	
	for( unsigned short r = 0; r < 6; ++r )
	{
		rainbow << " red = " << r << "  ";
		for( unsigned short g = 0; g < 6; ++g )
		{
			for( unsigned short b = 0; b < 6; ++b )
			{
				Color256 fg = Color256(r,g,b),
					 bg = Color256(r,g,b);
				rainbow << ColorCombination( &fg, &bg ) << "  ";
				rainbow << ColorCombination::resetColor() << "  ";
			}
			rainbow << "   ";
		}
		rainbow << ColorCombination::resetColor() << std::endl << std::endl;
	}

	return rainbow.str();
}


std::string EnumerateGrayscale()
{
	std::stringstream rainbow;
	for( unsigned short g = 0; g < 24; ++g )
	{
		rainbow.width( 2 );
		rainbow << std::right << g;
		rainbow << "  ";
	}
	rainbow << std::endl;

	for( unsigned short g = 0; g < 24; ++g )
	{
		GrayScale gray = GrayScale( g );
		rainbow << ColorCombination( &gray, &gray ) << "  ";
		rainbow << ColorCombination::resetColor() << "  ";
	}

	rainbow << ColorCombination::resetColor() << std::endl << std::endl;
	
	return rainbow.str();
}
