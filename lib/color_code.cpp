#include "color_code.h"

int Color256::value() const
{
	return 16 + 36*red + 6*green + blue;
}


int GrayScale::value() const
{
	return 0xe8 + gray;
}
