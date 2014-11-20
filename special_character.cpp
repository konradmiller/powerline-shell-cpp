#include "special_character.h"

static CharacterMapping init()
{
	CharacterMapping characters;
	characters[ "dots" ] = u8"\u2026";
	characters[ "esc" ]  = "\033[";

	return characters;
}


CharacterMapping SpecialCharacter::characters( init() );
