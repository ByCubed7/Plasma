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
		tiles[tile.position] = tile;
		//cout << "AddTile: " << tile.position.ToString() << endl;


		//cout << tile.position.ToString() << endl;
		//cout << tiles.size() << endl;

		// If the position is bigger than the total size, set the total size
		//if (position.x + 1 > width) width = position.x + 1;
		//if (position.y + 1 > height) height = position.y + 1;
	}


	// Generates and Returns a TileLayers render data
	TileRender TileLayer::GetRender()
	{
		TileRender renderData = TileRender();

		//cout << "size: " << tiles.size() << endl;

		for (auto& tile : tiles) {
			renderData.Add(tile.second);

			//cout << "GetRender: " << tile.second.position.ToString() << endl;
		}
		return renderData;
	}

	// - Gets

	int TileLayer::GetTileAt(Vector2 position)
	{
		return tiles[position].id;
	}

	size_t TileLayer::Count() { return tiles.size(); }
}