#include "special_character.h"

CharacterMapping init()
{
	CharacterMapping characters;
	characters[ "dots" ] = u8"\u2026";

	return characters;
}


CharacterMapping SpecialCharacter::characters( init() );
