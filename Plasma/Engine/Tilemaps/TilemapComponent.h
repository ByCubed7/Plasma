// By @ByCubed7 on Twitter

#pragma once

#include "../Component.h"
#include "Tilemap.h"

#include <vector>

class TilemapComponent : public Engine::Component
{
public:
	TilemapComponent(Engine::GameObject* gameObject, std::string name = "TilemapComponent");

	void update(double time, double delta, Engine::Scene& game) override;
	void draw(Render::Renderers& renderer) override;

	Tilemaps::Tilemap tilemap;

	glm::vec3 color;

	float animationPoint;
	float animationSpeed;
	int spriteFrame;

	TilemapComponent* bind(Render::Renderers* renderer);
	TilemapComponent* setTexture2D(Texture2D texture);
	TilemapComponent* setTilemap(const Tilemaps::Tilemap& tilemap);
	TilemapComponent* setTileSize(int size);

	Vector2 getTilePositionAtScenePosition(Vector2 pos);
	Vector2 getScenePositionAtTilePosition(Vector2 pos);

	// Getting tiles
	int  getTileAtScenePosition(Vector2 pos);
	bool isTileAtScenePosition(Vector2 pos);
};