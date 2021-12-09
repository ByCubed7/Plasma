// By @ByCubed7 on Twitter

#pragma once

#include "Component.h"
#include "Tilemaps/Tilemap.h"

#include <vector>

class TilemapComponent : public Component
{
public:
	TilemapComponent(std::string name = "TilemapComponent");

	void Update(double delta, Engine::Scene& game) override;
	void Draw(Render::Renderers& renderer) override;

	Tilemaps::Tilemap tilemap;

	glm::vec3 color;

	float animationPoint;
	float animationSpeed;
	int spriteFrame;

	TilemapComponent* Bind(Render::Renderers* renderer);
	TilemapComponent* Set(Texture2D texture);
	TilemapComponent* SetTilemap(const Tilemaps::Tilemap& tilemap);
	TilemapComponent* SetTileSize(pair<int, int> size);

	Vector2 GetTilePositionAtScenePosition(Vector2 pos);
	Vector2 GetTilePositionAtScenePosition(float x, float y);

	Vector2 SPosAtTPos(Vector2 pos);
	Vector2 SPosAtTPos(int x, int y);

	Vector2 GetTileDensity();


	// Getting tiles

	int GetTileAtScenePosition(Vector2 pos);
	int GetTileAtScenePosition(float x, float y);

	int GetTileAt(Vector2 pos);
	int GetTileAt(int x, int y);
};