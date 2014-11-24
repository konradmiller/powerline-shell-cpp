#include <iostream>

#include "color_code.h"
#include "color_combination.h"
#include "special_character.h"

#include "cwd.h"
#include "test_color.h"


int
main()
{
	std::cout << EnumerateColors() << EnumerateGrayscale();
	
	#include "themes/default.cpp"

	std::string reset = ColorCombination::resetColor();

	std::cout << white_on_gray << cwd::getSegment( white_on_gray );
	white_on_gray.inverse();
	std::cout << white_on_gray << special("separator") << reset;
	std::cout << std::endl;

	return 0;
}
