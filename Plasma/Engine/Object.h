// By @ByCubed7 on Twitter

#pragma once
#include <string>

using namespace std;

struct Object
{
	// Constructor
	Object(string name);

	// Returns the object type
	virtual string ToString();

	operator string();

protected:
	// The name of the object
	string name;
};

