#ifndef SPECIAL_CHARACTER_H__
#define SPECIAL_CHARACTER_H__

#include <map>
#include <string>

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



#endif
