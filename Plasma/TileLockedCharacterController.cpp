// By @ByCubed7 on Twitter

#include "TileLockedCharacterController.h"


TileLockedCharacterController::TileLockedCharacterController(std::string name)
	: Component(name)
{

}

TileLockedCharacterController* TileLockedCharacterController::SetTilemap(TilemapComponent* tilemapComponent)
{
	this->tilemapComp = tilemapComponent;
	return this;
}

void TileLockedCharacterController::Update(double delta, Scene& game)
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



	//bool isNextBlock = false;
	//cout << isNextBlock << " : ";
	//isNextBlock = isNextBlock || tilemapComp->GetTileAtScenePosition(gameObject->position + tilemapComp->GetTileDensity() * Vector2(0.01f, 0.01f) + inputDirection * delta) == -1;
	//cout << isNextBlock << " : ";
	//isNextBlock = isNextBlock || tilemapComp->GetTileAtScenePosition(gameObject->position + tilemapComp->GetTileDensity() * Vector2(0.99f, 0.01f) + inputDirection * delta) == -1;
	//cout << isNextBlock << " : ";
	//isNextBlock = isNextBlock || tilemapComp->GetTileAtScenePosition(gameObject->position + tilemapComp->GetTileDensity() * Vector2(0.01f, 0.99f) + inputDirection * delta) == -1;
	//cout << isNextBlock << " : ";
	//isNextBlock = isNextBlock || tilemapComp->GetTileAtScenePosition(gameObject->position + tilemapComp->GetTileDensity() * Vector2(0.99f, 0.99f) + inputDirection * delta) == -1;
	//cout << isNextBlock << endl;

	Vector2 tilePosition = tilemapComp->GetTilePositionAtScenePosition(gameObject->position);
	Vector2 tilePositionAtTarget = tilemapComp->GetTilePositionAtScenePosition(gameObject->position + inputDirection * delta);

	if (tilemapComp->GetTileAt(tilePositionAtTarget) == -1)
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
