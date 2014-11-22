#include <iostream>

#include "special_character.h"
#include "color_code.h"
#include "test_color.h"
#include "cwd.h"

int
main()
{
	std::cout	<< ColorCode::getBasicColorCode( ColorCode::GREEN, ColorCode::RED ) << special( "dots" )
			<< ColorCode::resetColor() << std::endl;
//	std::cout << ColorCode::EnumarateBasicColors() << std::endl;
	std::cout << Enumerate256Colors() << std::endl;

	std::cout << cwd::getSegment() << std::endl;

	return 0;
}
