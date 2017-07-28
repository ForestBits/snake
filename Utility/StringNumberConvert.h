//convert numers to strings and vice versa

#ifndef STRINGNUMBERCONVERT_H
#define STRINGNUMBERCONVERT_H

#include <sstream>
#include <string>

template <typename T>
inline std::string toString(T number)
{
	std::stringstream stream;

	stream << number;
   
	return stream.str();
}

template <typename T>
inline T toNumber(std::string string)
{
	std::stringstream stream(string);

	T number;

	stream >> number;

	return number;
}

#endif
