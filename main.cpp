#include <iostream>

#include "special_character.h"
#include "color_code.h"

int
main()
{
	std::cout << setColor( GREEN, RED ) << special( "dots" ) << resetColor() << std::endl;
	std::cout << ColorCode::EnumarateBasicColors();

	return 0;
}
