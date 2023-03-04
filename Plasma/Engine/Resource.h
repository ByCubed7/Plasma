// By @ByCubed7 on Twitter

#pragma once

#include <map>
#include <string>
#include <iostream>

template<class T>
class Resource 
{
public:
	static bool Has(std::string name) { return cache.find(name) != cache.end(); } // Returns whether the Resource has the obj cached
	static T Get(std::string name) { return cache[name]; } // Retrieves a cached objs.

	// Virtual static idiom
	static void Load(const std::string file, const std::string name)
	{
		if (!Has(name)) 
		{
			// NOTE: I dispise this implementation
			Resource* resource = (Resource*) (new T()); 
			cache[name] = resource->FromFile(file);
			//delete resource;
		}
		//return cache[name];
	}

	static void CleanUp() {
		// std:c++17
		//for (auto const& [key, val] : cache) {
		//	Resource* resource = (Resource*) &val;
		//	resource->Clear();
		//}

		typename std::map<std::string, T>::iterator it;
		for (it = cache.begin(); it != cache.end(); it++)
		{
			Resource* resource = (Resource*)&it->second;
			//if (resource != nullptr)
			resource->Clear();
		}
	}

protected:
	// All the objs we have cached
	static std::map<std::string, T> cache;

	//std::string filepath, name;

	virtual T FromFile(const std::string filepath) = 0;
	virtual void Clear() = 0;
};

template<class T>
std::map<std::string, T> Resource<T>::cache = std::map<std::string, T>();