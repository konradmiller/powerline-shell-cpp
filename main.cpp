#include <iostream>

#include "special_character.h"
#include "color_code.h"
#include "segments/cwd.h"

int
main()
{
//	std::cout << setColor( GREEN, RED ) << special( "dots" ) << resetColor() << std::endl;
//	std::cout << ColorCode::EnumarateBasicColors();

	std::cout << Cwd::getSegment() << std::endl;

	return 0;
}
