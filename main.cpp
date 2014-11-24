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

	std::cout << white_on_gray << " " << cwd::getSegment( white_on_gray );
	std::cout << ColorCombination( &darkgray, NULL ) << special("separator") << " ";
		
	std::cout << ColorCombination::resetColor() << std::endl;

	return 0;
}
