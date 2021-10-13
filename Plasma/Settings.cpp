#include <fstream>
#include <json/value.h>

#include "Settings.h"


void Settings::LoadFromFile() 
{
	std::ifstream people_file("people.json", std::ifstream::binary);
	people_file >> people;
}