#include <iostream>

#include "special_character.h"
#include "color_code.h"
#include "test_color.h"
#include "cwd.h"


int
main()
{
	// std::cout << EnumerateColors() << EnumerateGrayscale();
	#define COLOR(name)  ColorCombination name = ColorCombination
	#define RGB(a, b, c) Color((a), (b), (c))
	#define GRAY(a)      Color((a))
	#include "themes/default.cpp"
	std::string reset = ColorCombination::resetColor();

	std::cout << white_on_gray << cwd::getSegment( white_on_gray );
	white_on_gray.inverse();
	std::cout << white_on_gray << special("separator") << reset;
	std::cout << std::endl;

	return 0;
}
