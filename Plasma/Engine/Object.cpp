// By @ByCubed7 on Twitter


//#define VERBOSE

#include "Object.h"

// Constructor
Object::Object(std::string name)
{
	this->name = name;
}

// Returns the object type
std::string Object::ToString() { return name; }

// Operators

Object::operator std::string() { return ToString(); }