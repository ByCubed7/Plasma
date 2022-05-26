// By @ByCubed7 on Twitter

#include "All.h"

#include "WalkComponent.h"

#include <math.h>

WalkComponent::WalkComponent(Engine::GameObject* gameObject, std::string name)
	: Component(gameObject, name)
{
	target = 0;
	step = 5;
	wobble = Vector2({ 800, 10 });
}

void WalkComponent::Update(double time, double delta, Engine::Scene& game)
{
	float absoluteDistance = Vector2::Distance(absoluteTarget, target);
	float distance = Vector2::Distance(target, gameObject->position);

	if (absoluteDistance > 10)
		target = absoluteTarget;

	if (distance > 10) {
		stepCount += delta;

		Vector2 targetStep = Vector2(target - gameObject->position);
		targetStep.Normalize();

		gameObject->position += targetStep * step;
	}
	else if (abs(gameObject->rotation) > 3)
		stepCount += delta;

	gameObject->rotation = sin(stepCount * wobble.x * step) * wobble.y;

	gameObject->scale.x = abs(gameObject->scale.x) * (gameObject->position > target.x ? 1 : -1);
}

WalkComponent* WalkComponent::SetTargetPosition(Vector2 position)
{
	absoluteTarget = position;
	return this;
}
