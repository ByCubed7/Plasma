#include "Object.h"

// Constructor
Object::Object(string name) 
{
	this->name = name;
}

// Returns the object type
string Object::ToString() { return name; }