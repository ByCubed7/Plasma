// By @ByCubed7 on Twitter

#pragma once

#include "Tilemap.h"

#include <map>
#include <string>
#include <vector>

Tilemap::Tilemap()
{
	//width = 1;
	//height = 1;
}

void Tilemap::AddTile(Tile tile)
{
	tiles.push_back(tile);

	// If the position is bigger than the total size, set the total size
	//if (position.x + 1 > width) width = position.x + 1;
	//if (position.y + 1 > height) height = position.y + 1;
}

// Not the best way to do it?
void Tilemap::AddTile(int id, glm::vec2 position) {
	AddTile(Tile(id, position));
}
void Tilemap::AddTile(int id, glm::vec2 position, float rotation) {
	AddTile(Tile(id, position, rotation));
}
void Tilemap::AddTile(int id, glm::vec2 position, float rotation, glm::vec2 scale) {
	AddTile(Tile(id, position, rotation, scale));
}


// Generates and Returns a Tilemaps render data
Tilemap::Render Tilemap::GetRender()
{
	Render renderData = Render();

	for (auto& tile : tiles)
		renderData.Add(tile);

	return renderData;
}

// - Gets

int Tilemap::Count() { return tiles.size(); }
pair<int, int> Tilemap::TextureSize() { return tileSize; }


// ▀█▀ █ █   █▀▀
//  █  █ █▄▄ ██▄

Tilemap::Tile::Tile()
{
	id = 0;
	position = { 0,0 };
	rotation = 0;
	scale = { 1,1 };
}

Tilemap::Tile::Tile(int id, glm::vec2 position)
{
	this->id = id;
	this->position = position;
	rotation = 0;
	scale = { 1,1 };
}

Tilemap::Tile::Tile(int id, glm::vec2 position, float rotation)
{
	this->id = id;
	this->position = position;
	this->rotation = rotation;
	scale = { 1,1 };
}

Tilemap::Tile::Tile(int id, glm::vec2 position, float rotation, glm::vec2 scale)
{
	this->id = id;
	this->position = position;
	this->rotation = rotation;
	this->scale = scale;
}


// █▀█ █▀▀ █▄ █ █▀▄ █▀▀ █▀█ █▀▄ ▄▀█ ▀█▀ ▄▀█
// █▀▄ ██▄ █ ▀█ █▄▀ ██▄ █▀▄ █▄▀ █▀█  █  █▀█

void Tilemap::Render::Add(Tile tile)
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

vector<float> Tilemap::Render::Ids()
{
	vector<float> data;
	for (auto& tile : ids)
		data.push_back(tile);
	return data;
}

vector<glm::vec2> Tilemap::Render::Positions()
{
	return positions;
	/*
	vector<glm::vec2> data;
	for (auto& position : positions)
		data.push_back(position);
	return data;
	//*/
}

vector<glm::mat4> Tilemap::Render::RotScas()
{
	return rotscas;
}

int Tilemap::Render::Count()
{
	return ids.size();
}
