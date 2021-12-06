// By @ByCubed7 on Twitter

#pragma once

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
	void Tilemap::AddTile(int layer, Tile tile) { layers[layer].AddTile(tile); }

	// Not the best way to do it?
	void Tilemap::AddTile(int layer, int id, glm::vec2 position) {
		AddTile(layer, Tile(id, position));
	}
	void Tilemap::AddTile(int layer, int id, glm::vec2 position, float rotation) {
		AddTile(layer, Tile(id, position, rotation));
	}
	void Tilemap::AddTile(int layer, int id, glm::vec2 position, float rotation, glm::vec2 scale) {
		AddTile(layer, Tile(id, position, rotation, scale));
	}


	int Tilemap::GetTileAt(int layer, glm::vec2 position)
	{
		return layers[layer].GetTileAt(position);
	}

	int Tilemap::GetTileAt(int layer, pair<int, int> position) 
	{ return GetTileAt(layer, glm::vec2(position.first, position.second)); }

}