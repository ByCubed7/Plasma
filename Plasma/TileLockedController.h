// By @ByCubed7 on Twitter

#pragma once

#include "Core.h"
#include "Components.h"
#include "Tilemaps.h"

class TileLockedController : public Component
{
public:
	TileLockedController(GameObject* gameObject, std::string name = "TileLockedCharacterController");

	TilemapComponent* tilemapComp;

	Vector2 currentDirection = { 0,0 };
	Vector2 inputDirection = { 0,0 };
	float speed = 100;

	TileLockedController* SetTilemap(TilemapComponent* tilemapComponent);
	TileLockedController* SetSpeed(float speed);

	TileLockedController* SetInputDirection(Vector2 newInputDirection);
	TileLockedController* SetRotatable(bool newIsRotatable);
	Vector2 GetCurrentDirection();

	bool CanGoUp();
	bool CanGoDown();
	bool CanGoLeft();
	bool CanGoRight();

	void Update(double delta, Engine::Scene& game) override;

private:
	bool isRotatable;

	bool canGoUp;
	bool canGoDown;
	bool canGoLeft;
	bool canGoRight;
};

