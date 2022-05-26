// By @ByCubed7 on Twitter

#include "All.h"

#include "LockComponent.h"

#include <math.h>

LockComponent::LockComponent(Engine::GameObject* gameObject, std::string name)
	: Component(gameObject, name)
{
	target = gameObject;
}

void LockComponent::Update(double time, double delta, Engine::Scene& game)
{
	gameObject->position = target->position;
	//gameObject->rotation = target->rotation;
	gameObject->scale = target->scale;

}

LockComponent* LockComponent::SetTarget(Engine::GameObject* newTarget)
{
	target = newTarget;
	return this;
}