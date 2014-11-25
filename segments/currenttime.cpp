#include <iostream>
#include <chrono>
#include <ctime>

#include "color_code.h"
#include "special_character.h"

#include "currenttime.h"

namespace c = std::chrono;

namespace currenttime
{
	static std::string formatCurrentTime( const tm & );
	static tm getCurrentTime();


	std::string getSegment()
	{
		return formatCurrentTime( getCurrentTime() );
	}


	static tm getCurrentTime()
	{
		tm tm_value;

		std::time_t now = c::system_clock::to_time_t( c::system_clock::now() );
		assert( localtime_r( &now, &tm_value ) );

		return tm_value;
	}


	static std::string formatCurrentTime( const tm &tm_value )
	{
		const size_t TIME_STRING_SIZE = 1024;
		char time_buffer[TIME_STRING_SIZE];

		// TODO: use put_time as soon as gcc supports it
		auto ret = std::strftime( time_buffer, sizeof(time_buffer) / sizeof(char), "%T", &tm_value );

		// %T should return HH:MM:SS -> exactly 8 characters
		assert( ret == 8 );

		return std::string( time_buffer );
	}
}

