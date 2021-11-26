// By @ByCubed7 on Twitter

#pragma once

#include "Component.h"
#include "Tilemap.h"

class TilemapComponent : public Component
{
public:
	TilemapComponent(GameObject* gameObject, std::string name = "TilemapComponent");

	void Update(double delta, Game& game) override;
	void Draw(Renderer& renderer) override;

	Tilemap tilemap;

	glm::vec3 color;

	TilemapComponent* Bind(Renderer* renderer);
	TilemapComponent* Set(Texture2D texture);
	TilemapComponent* SetTileSize(tuple<int, int> size);
};