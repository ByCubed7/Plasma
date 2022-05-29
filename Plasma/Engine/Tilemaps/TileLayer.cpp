// By @ByCubed7 on Twitter


//#define VERBOSE

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

	void TileLayer::DeleteTile(Tile tile)
	{
		tiles.erase(tile.position);
	}

	Tile TileLayer::GetTile(Vector2Int position)
	{
		//position.Round(1);
		std::map<Vector2Int, Tile>::iterator tile = tiles.find(position);
		if (tile == tiles.end()) {
			std::cerr << "[TileLayer::GetTile] Can't find tile at " << position.ToString() << std::endl
				<< "Use TileLayer::IsTile(Vector2) to check whether a tile exists at location.";
		}
		return tile->second;
	}

	bool TileLayer::IsTile(Vector2Int position)
	{
		//position.Round(1);
		std::map<Vector2Int, Tile>::iterator tile = tiles.find(position);
		return tile != tiles.end();
	}
	
	TileRender TileLayer::GetRender()
	{
		TileRender renderData = TileRender();

		int i = 0;
		for (auto& tile : tiles) {

			//if (tile.second.position == VectorInt(0) && tile.second.id == 0) std::cout << "INDEX: " << i << std::endl;

			renderData.Add(tile.second);
			i++;
		}
		
		return renderData;
	}

	size_t TileLayer::Count() { return tiles.size(); }
}