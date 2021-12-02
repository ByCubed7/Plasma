// By @ByCubed7 on Twitter

#pragma once

#include "TileRender.h"
#include "Tile.h"


namespace Tilemaps {

	void TileRender::Add(Tile tile)
	{
		ids.push_back(tile.id);
		positions.push_back(tile.position);

		// Calculate rotation and scale matrix

		glm::mat4 transform = glm::mat4(1.0f);

		//*
		transform = glm::translate(transform, glm::vec3(tile.position.x, tile.position.y, 0.0f)); // move origin of rotation to center of quad
		transform = glm::rotate(transform, glm::radians(tile.rotation), glm::vec3(0.0f, 0.0f, 1.0f)); // rotate
		transform = glm::scale(transform, glm::vec3(tile.scale, 1.0f)); // scale
		transform = glm::translate(transform, glm::vec3(-tile.position.x, -tile.position.y, 0.0f)); // move origin back

		//*/
		//cout << glm::to_string(transform) << endl;

		rotscas.push_back(transform);
	}

	vector<float> TileRender::Ids()
	{
		vector<float> data;
		for (int& tile : ids)
			data.push_back((float)tile);
		return data;
	}

	vector<glm::vec2> TileRender::Positions()
	{
		return positions;
		/*
		vector<glm::vec2> data;
		for (auto& position : positions)
			data.push_back(position);
		return data;
		//*/
	}

	vector<glm::mat4> TileRender::RotScas()
	{
		return rotscas;
	}

	size_t TileRender::Count()
	{
		return ids.size();
	}
}