#include "special_character.h"

static CharacterMapping init()
{
	CharacterMapping characters;

	characters[ "dots" ]           = u8"\u2026";
	characters[ "esc" ]            = u8"\033";
	characters[ "lock" ]           = u8"\ue0a2";
	characters[ "network" ]        = u8"\ue0a2";
	characters[ "separator" ]      = u8"\ue0b0";
	characters[ "separator_thin" ] = u8"\ue0b1";

	return characters;
}


CharacterMapping SpecialCharacter::characters( init() );
