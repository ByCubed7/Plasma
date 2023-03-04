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
	
	sprite = gameObject->Get<SpriteComponent>();
}

void WalkComponent::Update(double time, double delta, Engine::Scene& game)
{
	float absoluteDistance = Vector2::Distance(absoluteTarget, target);
	float distance = Vector2::Distance(target, gameObject->position);

	if (absoluteDistance > 10)
		target = absoluteTarget;

	if (distance > 10) {
		stepCount += delta;

		Vector2 targetStep = target - gameObject->position;
		targetStep = targetStep.Normalize();

		gameObject->position += targetStep * step;
	}
	else if (abs(gameObject->rotation) > 3)
		stepCount += delta;

	gameObject->rotation = sin(stepCount * wobble.x * step) * wobble.y;

	if (sprite != nullptr)
		sprite->reflectionX = gameObject->position < target.x;
}

WalkComponent* WalkComponent::SetTargetPosition(Vector2 position)
{
	absoluteTarget = position;
	return this;
}
