#include "color_code.h"

std::string setColor( Color foreground, Color background )
{
	return ColorCode::getBasicColorCode( foreground, background );
}

