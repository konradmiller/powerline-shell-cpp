#include <iostream>

#include "special_character.h"
#include "color_code.h"
#include "test_color.h"
#include "cwd.h"

namespace CC = ColorCode;

int
main()
{
	std::string white_on_gray = CC::get256ColorCode(CC::Color256(5, 5, 5), CC::Color256(1, 1, 1));
	std::string gray_on_white = CC::get256ColorCode(CC::Color256(1, 1, 1), CC::Color256(5, 5, 5));
	std::string reset         = CC::resetColor();

	std::cout
		<< white_on_gray << cwd::getSegment( white_on_gray )
		<< gray_on_white << special("separator")
		<< reset << std::endl;

	return 0;
}
