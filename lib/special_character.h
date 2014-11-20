#ifndef SPECIAL_CHARACTER_H__
#define SPECIAL_CHARACTER_H__

#include <map>
#include <string>

/*
 * This might seem weird at first, the reasons for doing it this way are:
 * - Don't want global variables for all characters
 * - Don't want to think about where a container that stores all special characters is initialized outside of the class
 * - Don't want copies of the datastructure floating around
 * --> This here is basically a singleton that is merely called as
 *  	SpecialCharacter::get( "charactername" );
 * --> To save some time reading/typing you can just write
 *  	special( "charactername" )
 */

typedef std::map< std::string, std::string > CharacterMapping;

class SpecialCharacter
{
public:
	static std::string get( std::string name )
	{
		return characters[name];
	}
	

private:
	static CharacterMapping characters;

	// make sure that this singleton is not copied
	SpecialCharacter() {};
	SpecialCharacter( SpecialCharacter const& );
	void operator=( SpecialCharacter const& );
};


#define special(ch) SpecialCharacter::get( (ch) )


#endif
