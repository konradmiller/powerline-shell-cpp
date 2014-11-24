#ifndef TEST_COLOR_H__
#define TEST_COLOR_H__

#include <string>

class ColorCombination;

namespace enumeratecolors
{
	std::string getSegment( const ColorCombination& );

	std::string EnumerateColors();
	std::string EnumerateGrayscale();
}

#endif
