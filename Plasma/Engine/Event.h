// By @ByCubed7 on Twitter

#pragma once

#include <string>

using namespace std;

template <typename T>
class Event 
{
public:
	// Constructors
	Event() = default;
	Event(T type, const string& name = "") : _type(type), _name(name) {};
	
	inline const T type() const { return _type; };
	inline const string& getName() const { return _name; };
	virtual bool isHandled() { return _handled; };

protected:
	T _type;
	string _name;
	bool _handled = false;
};