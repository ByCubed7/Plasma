// By @ByCubed7 on Twitter

#include "AmbushGhostInputDirector.h"

AmbushGhostInputDirector::AmbushGhostInputDirector(GameObject* gameObject, std::string name)
	: InputDirector(gameObject, name)
{
	target = nullptr;
}

AmbushGhostInputDirector* AmbushGhostInputDirector::SetTarget(GameObject* newTarget) { target = newTarget; return this; }
AmbushGhostInputDirector* AmbushGhostInputDirector::SetStateComponent(GhostStateComponent* newStateComponent) { stateComponent = newStateComponent; return this; }

void AmbushGhostInputDirector::Update(double delta, Engine::Scene & game)
{
	Vector2 targetTile = controller->tilemapComp->GetTilePositionAtScenePosition(target->position);
	if (target->rotation ==	  0) targetTile += Vector2::right * 4;
	if (target->rotation ==  90) targetTile += Vector2::up	  * 4;
	if (target->rotation == 180) targetTile += Vector2::left  * 4;
	if (target->rotation == 270) targetTile += Vector2::down  * 4;

	Vector2 positionTile = controller->tilemapComp->GetTilePositionAtScenePosition(gameObject->position);

	Vector2 currentDirection = controller->GetCurrentDirection();

	if (Vector2::Distance(lastTurnPoint, positionTile) > 1)
	{
		bool canGoUp	= controller->CanGoUp();
		bool canGoDown	= controller->CanGoDown();
		bool canGoLeft	= controller->CanGoLeft();
		bool canGoRight = controller->CanGoRight();

		int pointsUp	= 0;
		int pointsDown	= 0;
		int pointsLeft	= 0;
		int pointsRight = 0;

		pointsUp	-= (int) Vector2::Distance(positionTile + Vector2( 0,-1), targetTile);
		pointsDown	-= (int)Vector2::Distance(positionTile + Vector2( 0, 1), targetTile);
		pointsLeft	-= (int)Vector2::Distance(positionTile + Vector2(-1, 0), targetTile);
		pointsRight -= (int)Vector2::Distance(positionTile + Vector2( 1, 0), targetTile);

		pointsUp	+= canGoUp		? 8 : 0;
		pointsDown	+= canGoDown	? 8 : 0;
		pointsLeft	+= canGoLeft	? 8 : 0;
		pointsRight += canGoRight	? 8 : 0;

		pointsUp	+= Vector2( 0, 1) != currentDirection ? 8 : 0;
		pointsDown	+= Vector2( 0,-1) != currentDirection ? 8 : 0;
		pointsLeft	+= Vector2( 1, 0) != currentDirection ? 8 : 0;
		pointsRight += Vector2(-1, 0) != currentDirection ? 8 : 0;

		if (pointsUp > pointsDown && pointsUp > pointsLeft && pointsUp > pointsRight) inputDirection = Vector2(0, -1);
		else if (pointsDown > pointsLeft && pointsDown > pointsRight) inputDirection = Vector2(0, 1);
		else if (pointsLeft > pointsRight) inputDirection = Vector2(-1, 0);
		else inputDirection = Vector2(1, 0);

		PassInputDirection();

		if (canGoUp + canGoDown + canGoLeft + canGoRight > 2) {
			lastTurnPoint = positionTile;
		}
		else lastTurnPoint = Vector2::zero;
	}
}
