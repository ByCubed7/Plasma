// By @ByCubed7 on Twitter

#include "Resource.h"

#include <map>

template <class T>
std::map<std::string, T> Resource<T>::cache;

//template <class T>
//T Resource<T>::Load(std::string name) {}

template <class T>
T& Resource<T>::Get(std::string name) {
	return cache[name];
}

template <class T>
bool Resource<T>::Has(std::string name) {
	return cache.contains(name);
}