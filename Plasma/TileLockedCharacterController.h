// By @ByCubed7 on Twitter

#pragma once

#include "Engine/Tilemaps/Tilemap.h"

#include "Engine/Vector2.h"
#include "Engine/Component.h"
#include "Engine/TilemapComponent.h"

class TileLockedCharacterController : public Component
{
public:
	TileLockedCharacterController(GameObject* gameObject, std::string name = "TileLockedCharacterController");

	TilemapComponent* tilemapComp;

	Vector2 currentDirection = { 0,0 };
	Vector2 inputDirection = { 0,0 };
	float speed = 100;

	TileLockedCharacterController* SetTilemap(TilemapComponent* tilemapComponent);
	TileLockedCharacterController* SetSpeed(float speed);

	void Update(double delta, Engine::Scene& game) override;
};

