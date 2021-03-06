// By @ByCubed7 on Twitter

#include "All.h"

#include "LockComponent.h"

#include <math.h>

LockComponent::LockComponent(Engine::GameObject* gameObject, std::string name)
	: Component(gameObject, name)
{
	target = gameObject;

	lockPosition = false;
	lockRotation = false;
	lockScale = false;

	positionOffset = { 0,0 };
	rotationOffset = 0;
	scaleOffset = { 0, 0 };

	gameObjectSprite = nullptr;
	targetSprite = nullptr;

}

void LockComponent::Update(double time, double delta, Engine::Scene& game)
{
	if (lockPosition) gameObject->position = target->position + positionOffset * target->scale;
	if (lockRotation) gameObject->rotation = target->rotation + rotationOffset;
	if (lockScale)    gameObject->scale = target->scale + scaleOffset;
	
	if (gameObjectSprite != nullptr && targetSprite != nullptr)
		gameObjectSprite->reflection = targetSprite->reflection;
}

LockComponent* LockComponent::SetTarget(Engine::GameObject* newTarget)
{
	target = newTarget;
	return this;
}

LockComponent* LockComponent::LockPosition(bool doLock)
{
	lockPosition = doLock;
	return this;
}

LockComponent* LockComponent::LockRotation(bool doLock)
{
	lockRotation = doLock;
	return this;
}

LockComponent* LockComponent::LockScale(bool doLock)
{
	lockScale = doLock;
	return this;
}

LockComponent* LockComponent::LockSpriteReflection(SpriteComponent* newSprite)
{
	gameObjectSprite = gameObject->Get<SpriteComponent>();
	targetSprite = newSprite;
	return this;
}

LockComponent* LockComponent::SetPositionOffset(Vector2Float value)
{
	positionOffset = value;
	return this;
}

LockComponent* LockComponent::SetRotationOffset(float value)
{
	positionOffset = value;
	return this;
}

LockComponent* LockComponent::SetScaleOffset(Vector2Float value)
{
	positionOffset = value;
	return this;
}
