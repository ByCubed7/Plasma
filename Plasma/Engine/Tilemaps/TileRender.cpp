﻿// By @ByCubed7 on Twitter


//#define VERBOSE

#include "TileRender.h"
#include "Tile.h"


namespace Tilemaps {

	void TileRender::add(const Tile& tile)
	{
		//if (tile.position == 0 && tile.id == 0) return;
		
		ids.push_back(tile.id);

		glm::vec2 position(tile.position.x, tile.position.y);
		positions.push_back(position);

		// Calculate rotation and scale matrix

		glm::mat4 transform = glm::mat4(1.0f);

		//*
		transform = glm::translate(transform, glm::vec3(position, 0.0f)); // move origin of rotation to center of quad
		transform = glm::rotate(transform, glm::radians(tile.rotation), glm::vec3(0.0f, 0.0f, 1.0f)); // rotate
		transform = glm::scale(transform, glm::vec3(tile.scale.x, tile.scale.y, 1.0f)); // scale
		transform = glm::translate(transform, glm::vec3(-position, 0.0f)); // move origin back

		//*/
		//cout << glm::to_string(transform) << endl;

		rotscas.push_back(transform);
	}

	const size_t& TileRender::size() const
	{
		return ids.size();
	}
}