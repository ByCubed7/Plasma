#include "TileLockedController.h"
#include "TileLockedController.h"
#include "TileLockedController.h"
#include "TileLockedController.h"
#include "TileLockedController.h"
#include "TileLockedController.h"
// By @ByCubed7 on Twitter

#include "TileLockedController.h"


TileLockedController::TileLockedController(GameObject* gameObject, std::string name)
	: Component(gameObject, name)
{}

TileLockedController* TileLockedController::SetTilemap(TilemapComponent* tilemapComponent)
{
	this->tilemapComp = tilemapComponent;
	return this;
}

TileLockedController* TileLockedController::SetSpeed(float speed)
{
	this->speed = speed;
	return this;
}

TileLockedController* TileLockedController::SetInputDirection(Vector2 newInputDirection)
{
	inputDirection = newInputDirection;
	return this;
}

TileLockedController* TileLockedController::SetRotatable(bool newIsRotatable)
{
	isRotatable = newIsRotatable;
	return this;
}

Vector2 TileLockedController::GetCurrentDirection() { return currentDirection; }

bool TileLockedController::CanGoUp()	{ return canGoUp;	 }
bool TileLockedController::CanGoDown()	{ return canGoDown;  }
bool TileLockedController::CanGoLeft()	{ return canGoLeft;  }
bool TileLockedController::CanGoRight() { return canGoRight; }

void TileLockedController::Update(double delta, Engine::Scene& game)
{
	//

	Vector2 tilePosition = tilemapComp->GetTilePositionAtScenePosition(gameObject->position);

	canGoUp		= !tilemapComp->tilemap.layers[0].IsTile(tilePosition + Vector2(0, -1));
	canGoDown	= !tilemapComp->tilemap.layers[0].IsTile(tilePosition + Vector2(0, 1));
	canGoLeft	= !tilemapComp->tilemap.layers[0].IsTile(tilePosition + Vector2(-1, 0));
	canGoRight	= !tilemapComp->tilemap.layers[0].IsTile(tilePosition + Vector2(1, 0));

	if (canGoUp		&& inputDirection == Vector2( 0,-1)) currentDirection = inputDirection;
	if (canGoDown	&& inputDirection == Vector2( 0, 1)) currentDirection = inputDirection;
	if (canGoLeft	&& inputDirection == Vector2(-1, 0)) currentDirection = inputDirection;
	if (canGoRight	&& inputDirection == Vector2( 1, 0)) currentDirection = inputDirection;


	//currentDirection = inputDirection;

	Vector2 nextPosition = gameObject->position + currentDirection * speed * delta;
	nextPosition -= tilemapComp->gameObject->position;
	nextPosition /= tilemapComp->GetTileDensity();
	nextPosition += 1;

	if (!tilemapComp->tilemap.layers[0].IsTile(nextPosition)) {
		gameObject->position += currentDirection * speed * delta;
	}

	// - Tile Snapping
	// TODO: Smoothen the transmision

	if (!canGoUp)
		gameObject->position.y = std::max(
			gameObject->position.y,
			tilemapComp->GetScenePositionAtTilePosition(tilePosition).y
		);

	if (!canGoDown)
		gameObject->position.y = std::min(
			gameObject->position.y,
			tilemapComp->GetScenePositionAtTilePosition(tilePosition).y
		);

	if (!canGoLeft)
		gameObject->position.x = std::max(
			gameObject->position.x,
			tilemapComp->GetScenePositionAtTilePosition(tilePosition).x
		);

	if (!canGoRight)
		gameObject->position.x = std::min(
			gameObject->position.x,
			tilemapComp->GetScenePositionAtTilePosition(tilePosition).x
		);
	
	//

	// Rotation
	if (isRotatable) {
		if (currentDirection == Vector2::up   )	gameObject->rotation = 90;
		if (currentDirection == Vector2::down )	gameObject->rotation = 270;
		if (currentDirection == Vector2::left )	gameObject->rotation = 180;
		if (currentDirection == Vector2::right) gameObject->rotation = 0;
	}
}
