// By @ByCubed7 on Twitter

#pragma once

#include <map>
#include <string>

// Most likely an anti-pattern, but I can't figure out a proper implementation at this time.

template<class T>
class Resource {
public:
	static bool Has(std::string name) { return cache.find(name) != cache.end(); } // Returns whether the Resource has the obj cached
	static T Get(std::string name) { return cache[name]; } // Retrieves a cached objs.

	// Virtual static idiom
	static void Load(const std::string file, const std::string name)
	{
		if (!Has(name)) 
		{
			Resource* resource = (Resource*)(new T()); // I dispise this implementation
			cache[name] = resource->FromFile(file);
			//delete resource;
		}
		//return cache[name];
	}

	static void CleanUp() {
		for (auto const& [key, val] : cache) {
			Resource* resource = (Resource*) &val;
			resource->Clear();
		}
	}

protected:
	// All the objs we have cached
	static inline std::map<std::string, T> cache = std::map<std::string, T>();

	//std::string filepath, name;

	virtual T FromFile(const std::string filepath) = 0;
	virtual void Clear() = 0;
};