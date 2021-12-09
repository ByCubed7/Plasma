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
	if (game.input.IsKey(Input::Key_D)) inputDirection = { 10,0 };
	else if (game.input.IsKey(Input::Key_A)) inputDirection = { -10,0 };

	if (game.input.IsKey(Input::Key_S)) inputDirection = { 0,10 };
	else if (game.input.IsKey(Input::Key_W)) inputDirection = { 0,-10 };

	// Normilize velo
	if (inputDirection.Magnitude())
	{
		inputDirection.Normalize();
		inputDirection = inputDirection * speed;
	}

	//

	Vector2 tilePosition = tilemapComp->GetTilePositionAtScenePosition(gameObject->position);
	Vector2 tilePositionAtTarget = tilemapComp->GetTilePositionAtScenePosition(gameObject->position + inputDirection * delta);

	Vector2 position = gameObject->position + inputDirection * delta;
	position -= tilemapComp->gameObject->position;
	position /= tilemapComp->GetTileDensity();
	position += Vector2(1.5f);

	if (tilemapComp->GetTileAt(position) == -1)
	{
		gameObject->position += inputDirection * delta;
		currentDirection = inputDirection;
	}



	// Rotation
	if (game.input.IsKey(Input::Key_W)) gameObject->rotation = 270;
	if (game.input.IsKey(Input::Key_A)) gameObject->rotation = 180;
	if (game.input.IsKey(Input::Key_S)) gameObject->rotation = 90;
	if (game.input.IsKey(Input::Key_D)) gameObject->rotation = 0;

}
