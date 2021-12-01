// By @ByCubed7 on Twitter

#pragma once

#include "Component.h"
#include "Tilemaps/Tilemap.h"

class TilemapComponent : public Component
{
public:
	TilemapComponent(GameObject* gameObject, std::string name = "TilemapComponent");

	void Update(double delta, Game& game) override;
	void Draw(Renderers& renderer) override;

	Tilemaps::Tilemap tilemap;

	glm::vec3 color;

	float animationPoint;
	float animationSpeed;
	int spriteFrame;

	TilemapComponent* Bind(Renderers* renderer);
	TilemapComponent* Set(Texture2D texture);
	TilemapComponent* SetTilemap(const Tilemaps::Tilemap& tilemap);
	TilemapComponent* SetTileSize(pair<int, int> size);
};