// By @ByCubed7 on Twitter

#pragma once

#include "Tile.h"

namespace Tilemaps {

	Tile::Tile()
	{
		id = 0;
		position = { 0,0 };
		rotation = 0;
		scale = { 1,1 };
	}

	Tile::Tile(int id, Vector2 position)
	{
		this->id = id;
		this->position = position;
		rotation = 0;
		scale = { 1,1 };
	}

	Tile::Tile(int id, Vector2 position, float rotation)
	{
		this->id = id;
		this->position = position;
		this->rotation = rotation;
		scale = { 1,1 };
	}

	Tile::Tile(int id, Vector2 position, float rotation, Vector2 scale)
	{
		this->id = id;
		this->position = position;
		this->rotation = rotation;
		this->scale = scale;
	}
}