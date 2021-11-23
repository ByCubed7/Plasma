#pragma once

#include "Tilemap.h"

Tilemap::Tilemap()
{
	width = 0;
	height = 0;
}

void Tilemap::AddTile(tuple<int, int> position, int id)
{
	// We assume both elements of position are positive
	
	tiles[position] = id;

	// If the position is bigger than the total size, set the total size
	if (get<0>(position) > width) width = get<0>(position);
	if (get<1>(position) > height) height = get<1>(position);
}

// Gets

int Tilemap::Count() { return tiles.size(); }
tuple<int, int> Tilemap::TextureSize() { return tileSize; }


// Binds the textures as the current active GL_TEXTURE_2D texture object
void Tilemap::Bind()
{
	tileSheet.Bind();
}
