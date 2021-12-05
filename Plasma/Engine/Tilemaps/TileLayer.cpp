// By @ByCubed7 on Twitter

#pragma once

#include "TileLayer.h"

#include <map>
#include <string>
#include <vector>

namespace Tilemaps {
	TileLayer::TileLayer()
	{
		//width = 1;
		//height = 1;
	}

	void TileLayer::AddTile(Tile tile)
	{
		tiles.push_back(tile);

		// If the position is bigger than the total size, set the total size
		//if (position.x + 1 > width) width = position.x + 1;
		//if (position.y + 1 > height) height = position.y + 1;
	}

	// Not the best way to do it?
	void TileLayer::AddTile(int id, glm::vec2 position) {
		AddTile(Tile(id, position));
	}
	void TileLayer::AddTile(int id, glm::vec2 position, float rotation) {
		AddTile(Tile(id, position, rotation));
	}
	void TileLayer::AddTile(int id, glm::vec2 position, float rotation, glm::vec2 scale) {
		AddTile(Tile(id, position, rotation, scale));
	}


	// Generates and Returns a TileLayers render data
	TileRender TileLayer::GetRender()
	{
		TileRender renderData = TileRender();

		for (auto& tile : tiles)
			renderData.Add(tile);

		return renderData;
	}

	// - Gets

	int TileLayer::GetTileAt(glm::vec2 position)
	{
		for (auto& currentTile : tiles)
			if (currentTile.position == position)
				return currentTile.id;
		return -1;
	}

	int TileLayer::GetTileAt(pair<int, int> position)
	{ return GetTileAt(glm::vec2(position.first, position.second)); }

	size_t TileLayer::Count() { return tiles.size(); }

}