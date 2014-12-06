#include <iostream>

#include "color_code.h"
#include "color_combination.h"
#include "special_character.h"

#include "currenttime.h"
#include "cwd.h"
#include "enumeratecolors.h"
#include "git.h"

int
main()
{
	
	#include "themes/default.cpp"

//	std::cout << white_on_gray << " " << enumeratecolors::getSegment( white_on_gray );
//	std::cout << ColorCombination( NULL, &darkgray) << special("separator");

	std::cout << white_on_gray << " " << currenttime::getSegment();
	std::cout << ColorCombination( &lightgray, &darkgray ) << " " << special("separator_thin") << " ";

	std::cout << white_on_gray << " " << git::getSegment();
	std::cout << ColorCombination( &lightgray, &darkgray ) << " " << special("separator_thin") << " ";	
	
	std::cout << white_on_gray << " " << cwd::getSegment();
	std::cout << ColorCombination( &darkgray, NULL ) << special("separator") << " ";
		
	std::cout << ColorCombination::resetColor() << std::endl;

	return 0;
}
