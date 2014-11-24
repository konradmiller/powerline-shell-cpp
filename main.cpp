#include <iostream>

#include "color_code.h"
#include "color_combination.h"
#include "special_character.h"

#include "cwd.h"
#include "enumeratecolors.h"


int
main()
{
	
	#include "themes/default.cpp"

	std::cout << white_on_gray << " " << enumeratecolors::getSegment( white_on_gray );
	std::cout << ColorCombination( NULL, &darkgray) << special("separator");

	std::cout << white_on_gray << " " << cwd::getSegment( white_on_gray );
	std::cout << ColorCombination( &darkgray, NULL ) << special("separator") << " ";
		
	std::cout << ColorCombination::resetColor() << std::endl;

	return 0;
}
