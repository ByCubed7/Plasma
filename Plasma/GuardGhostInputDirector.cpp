// By @ByCubed7 on Twitter

#include "GuardGhostInputDirector.h"

GuardGhostInputDirector::GuardGhostInputDirector(GameObject* gameObject, std::string name)
	: InputDirector(gameObject, name)
{
	target = nullptr;
	stateComponent = nullptr;
}

GuardGhostInputDirector* GuardGhostInputDirector::SetTarget(GameObject* newTarget) { target = newTarget; return this; }
GuardGhostInputDirector* GuardGhostInputDirector::SetStateComponent(GhostStateComponent* newStateComponent) { stateComponent = newStateComponent; return this; }

void GuardGhostInputDirector::Update(double delta, Engine::Scene & game)
{
	Vector2 targetTile	 = controller->tilemapComp->GetTilePositionAtScenePosition(target->position);
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

		pointsUp	-= Vector2::Distance(positionTile + Vector2( 0,-1), targetTile);
		pointsDown	-= Vector2::Distance(positionTile + Vector2( 0, 1), targetTile);
		pointsLeft	-= Vector2::Distance(positionTile + Vector2(-1, 0), targetTile);
		pointsRight -= Vector2::Distance(positionTile + Vector2( 1, 0), targetTile);

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
