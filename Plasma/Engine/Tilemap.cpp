// By @ByCubed7 on Twitter

#pragma once

#include "Tilemap.h"

#include <glm/fwd.hpp>

#include <map>
#include <string>
#include <vector>

Tilemap::Tilemap()
{
	width = 1;
	height = 1;
}

void Tilemap::AddTile(pair<int, int> position, int id)
{
	// We assume both elements of position are positive
	tiles[position] = id;

	// If the position is bigger than the total size, set the total size
	if (get<0>(position) + 1 > width) width = get<0>(position) + 1;
	if (get<1>(position) + 1 > height) height = get<1>(position) + 1;
}

// Gets

int Tilemap::Count() { return tiles.size(); }
pair<int, int> Tilemap::TextureSize() { return tileSize; }

// Returns the Tilemaps render data
Tilemap::RenderData Tilemap::GetRenderData()
{
	RenderData renderData = RenderData();

	for (auto& tile : tiles) {
		renderData.tilePosition.push_back(tile.first);
		renderData.tileId.push_back(tile.second);
	}

	return renderData;
}