#pragma once
#include <string>

using namespace std;

struct Object
{
	// Constructor
	Object(string name);

	// Returns the object type
	virtual string ToString();

private:
	// The name of the object
	string name;
};

