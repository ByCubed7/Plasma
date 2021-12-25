// By @ByCubed7 on Twitter

#include "TileLockedCharacterController.h"


TileLockedCharacterController::TileLockedCharacterController(GameObject* gameObject, std::string name)
	: Component(gameObject, name)
{}

TileLockedCharacterController* TileLockedCharacterController::SetTilemap(TilemapComponent* tilemapComponent)
{
	this->tilemapComp = tilemapComponent;
	return this;
}

TileLockedCharacterController* TileLockedCharacterController::SetSpeed(float speed)
{
	this->speed = speed;
	return this;
}

void TileLockedCharacterController::Update(double delta, Engine::Scene& game)
{
	// Velocity
	if		(game.input.IsKey(Input::Key_W)) inputDirection = {  0,-1 };
	else if (game.input.IsKey(Input::Key_A)) inputDirection = { -1, 0 };
	else if (game.input.IsKey(Input::Key_S)) inputDirection = {  0, 1 };
	else if (game.input.IsKey(Input::Key_D)) inputDirection = {  1, 0 };

	//

	Vector2 tilePosition = tilemapComp->GetTilePositionAtScenePosition(gameObject->position);
	
	Vector2 targetTilePosition = tilePosition + inputDirection;

	Vector2 tilePositionAtTarget = tilemapComp->GetTilePositionAtScenePosition(gameObject->position + currentDirection * delta);

	//currentDirection = inputDirection;

	Vector2 nextPosition = gameObject->position + currentDirection * speed * delta;
	nextPosition -= tilemapComp->gameObject->position;
	nextPosition /= tilemapComp->GetTileDensity();
	nextPosition += 1;

	if (!tilemapComp->tilemap.layers[0].IsTile(nextPosition)) {
		gameObject->position += currentDirection * speed * delta;
	}

	// ABOVE
	if (tilemapComp->tilemap.layers[0].IsTile(tilePosition + Vector2(0, -1)))
	{
		gameObject->position.y = std::max(
			gameObject->position.y,
			tilemapComp->GetScenePositionAtTilePosition(tilePosition).y
		);
	}
	else if (inputDirection == Vector2(0, -1))
		currentDirection = inputDirection;

	// BELOW
	if (tilemapComp->tilemap.layers[0].IsTile(tilePosition + Vector2(0, 1)))
	{
		gameObject->position.y = std::min(
			gameObject->position.y,
			tilemapComp->GetScenePositionAtTilePosition(tilePosition).y
		);
	}
	else if (inputDirection == Vector2(0, 1))
		currentDirection = inputDirection;

	// LEFT
	if (tilemapComp->tilemap.layers[0].IsTile(tilePosition + Vector2(-1, 0)))
	{
		gameObject->position.x = std::max(
			gameObject->position.x,
			tilemapComp->GetScenePositionAtTilePosition(tilePosition).x
		);
	}
	else if (inputDirection == Vector2(-1, 0))
		currentDirection = inputDirection;

	// RIGHT
	if (tilemapComp->tilemap.layers[0].IsTile(tilePosition + Vector2(1, 0)))
	{
		gameObject->position.x = std::min(
			gameObject->position.x,
			tilemapComp->GetScenePositionAtTilePosition(tilePosition).x
		);
	}
	else if (inputDirection == Vector2(1, 0))
		currentDirection = inputDirection;
	
	//

	// Rotation
	if (currentDirection == Vector2::up   )	gameObject->rotation = 90;
	if (currentDirection == Vector2::down )	gameObject->rotation = 270;
	if (currentDirection == Vector2::left )	gameObject->rotation = 180;
	if (currentDirection == Vector2::right) gameObject->rotation = 0;

}
