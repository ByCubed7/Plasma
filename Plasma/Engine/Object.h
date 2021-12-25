// By @ByCubed7 on Twitter

#pragma once
#include <string>

struct Object
{
	// Constructor
	Object(std::string name);

	// Returns the object type
	virtual std::string ToString();

	operator std::string();

protected:
	// The name of the object
	std::string name;
};

