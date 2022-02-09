// By @ByCubed7 on Twitter

#include "All.h"
//#define VERBOSE

#include "Tilemap.h"

#include <map>
#include <string>
#include <vector>


namespace Tilemaps {
	Tilemap::Tilemap() {}

	void Tilemap::AddLayer(TileLayer layer)
	{
		layers.push_back(layer);
	}

	void Tilemap::AddLayer() { AddLayer(TileLayer()); }

}