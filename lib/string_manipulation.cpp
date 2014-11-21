#include <string>
#include <iostream>

#include "string_manipulation.h"

std::string
replaceFirstSubstring( const std::string &source, const std::string &from, const std::string &to )
{
	size_t matched_position = source.find( from, 0 );
	if( matched_position == std::string::npos )
		return source;

	std::string destination = source.substr( 0, matched_position ) + to;

	if( matched_position + from.length() < source.length() )
		destination += source.substr( matched_position + from.length() );
	
	return destination;
}

std::string
replaceAllSubstrings( const std::string &source, const std::string &from, const std::string &to )
{
	std::string destination = source;
	while( destination.find(from, 0) != std::string::npos )
		destination = replaceFirstSubstring( destination, from, to );

	return destination;
}
