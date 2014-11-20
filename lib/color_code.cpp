#include "color_code.h"

std::string setColor( Color foreground, Color background, bool bright, ColorVariant variant )
{
	return ColorCode::getBasicColorCode( foreground, background );
}

