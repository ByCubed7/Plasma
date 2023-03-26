// By @ByCubed7 on Twitter

#pragma once

#include "../Component.h"
#include "Tilemap.h"

#include <vector>

class TilemapComponent : public Engine::Component
{
public:
	TilemapComponent(Engine::GameObject* gameObject, std::string name = "TilemapComponent");

	void Update(double time, double delta, Engine::Scene& game) override;
	void Draw(Render::Renderers& renderer) override;

	Tilemaps::Tilemap tilemap;

	glm::vec3 color;

	float animationPoint;
	float animationSpeed;
	int spriteFrame;

	TilemapComponent* Bind(Render::Renderers* renderer);
	TilemapComponent* Set(Texture2D texture);
	TilemapComponent* SetTilemap(const Tilemaps::Tilemap& tilemap);
	TilemapComponent* SetTileSize(int size);

	Vector2 GetTilePositionAtScenePosition(Vector2 pos);
	Vector2 GetScenePositionAtTilePosition(Vector2 pos);


	// Getting tiles
	int GetTileAtScenePosition(Vector2 pos);
	bool IsTileAtScenePosition(Vector2 pos);
};