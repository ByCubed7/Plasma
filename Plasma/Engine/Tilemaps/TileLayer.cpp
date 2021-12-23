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

	void TileLayer::SetTile(Tile tile)
	{
		tiles[tile.position] = tile;
	}

	Tile TileLayer::GetTile(Vector2 position)
	{
		map<Vector2, Tile>::iterator tile = tiles.find(position);
		if (tile == tiles.end()) {
			cerr << "[TileLayer::GetTile] Can't find tile at " << position.ToString() << endl
				<< "Use TileLayer::IsTile(Vector2) to check whether a tile exists at location.";
		}
		return tile->second;
	}

	bool TileLayer::IsTile(Vector2 position)
	{
		map<Vector2, Tile>::iterator tile = tiles.find(position);
		return tile != tiles.end();
	}
	
	TileRender TileLayer::GetRender()
	{
		TileRender renderData = TileRender();

		int i = 0;
		for (auto& tile : tiles) {

			if (tile.second.position == 0 && tile.second.id == 0) cout << "INDEX: " << i << endl;

			renderData.Add(tile.second);
			i++;
		}
		
		return renderData;
	}

	size_t TileLayer::Count() { return tiles.size(); }
}