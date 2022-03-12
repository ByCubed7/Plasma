// By @ByCubed7 on Twitter

#include "All.h"

#include "WalkComponent.h"

#include <math.h>

WalkComponent::WalkComponent(Engine::GameObject* gameObject, std::string name)
	: Component(gameObject, name)
{
	target = 0;
	step = 1;
	wobble = Vector2(100,10);
}

void WalkComponent::Update(double delta, Engine::Scene& game)
{
	//std::cout << absoluteTarget.ToString() << std::endl;
	//gameObject->position = absoluteTarget;
	//return;

	float absoluteDistance = Vector2::Distance(absoluteTarget, target);
	float distance = Vector2::Distance(target, gameObject->position);

	if (absoluteDistance > 10)
		target = absoluteTarget;

	if (distance > 10) {
		stepCount++;

		Vector2 targetStep = Vector2(target - gameObject->position);
		targetStep.Normalize();

		gameObject->position += targetStep;
	}
	else if (abs(gameObject->rotation) > 3)
		stepCount++;

	gameObject->rotation = sin(wobble.x * stepCount) * wobble.y;

	gameObject->scale.x = abs(gameObject->scale.x) * (gameObject->position > target.x ? 1 : -1);
	//std::cout << stepCount << std::endl;
}

WalkComponent* WalkComponent::SetTargetPosition(Vector2 position)
{
	absoluteTarget = position;
	return this;
}
