// By @ByCubed7 on Twitter


//#define VERBOSE

#include "Tileset.h"

#include <iostream>

namespace Tilemaps {

	Tileset::Tileset() {}

	void Tileset::AddIndex(unsigned int id, unsigned int index)
	{
		idToIndex[id] = index;
	}

	unsigned int Tileset::GetIndexFromId(unsigned int id)
	{
		//if (id == 0) { cout << "[Tileset::GetIndexFromId] Id is '0', can't get index as tile doesn't exist" << endl;  return 0; }
		return id - 1; // idToIndex[id];
	}
}