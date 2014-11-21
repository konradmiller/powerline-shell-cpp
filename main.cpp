#include <iostream>

#include "special_character.h"
#include "color_code.h"
#include "segments/cwd.h"

int
main()
{
	std::cout << setColor( GREEN, RED ) << special( "dots" ) << resetColor() << std::endl;
//	std::cout << ColorCode::EnumarateBasicColors() << std::endl;
	std::cout << ColorCode::Enumerate256Colors() << std::endl;

	std::cout << cwd::getSegment() << std::endl;

	return 0;
}
