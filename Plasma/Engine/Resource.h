// By @ByCubed7 on Twitter

#pragma once

#include <map>
#include <string>

template<class T>
class Resource {
public:
	// Loads objs from file.
	//virtual T Load(std::string name) = 0;

	// Retrieves a cached objs.
	static T& Get(std::string name);;

	// Returns whether the Resource has the obj cached
	static bool Has(std::string name);

protected:
	// All the objs we have cached
	static std::map<std::string, T> cache;
};