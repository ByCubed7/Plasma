// By @ByCubed7 on Twitter

#pragma once

#include "Core.h"

class LockComponent : public Engine::Component
{
public:
	LockComponent(Engine::GameObject* gameObject, std::string name = "LockComponent");

	void update(double time, double delta, Engine::Scene& game) override;

	LockComponent* SetTarget(Engine::GameObject* target);

	LockComponent* LockPosition(bool doLock = true);
	LockComponent* LockRotation(bool doLock = true);
	LockComponent* LockScale(bool doLock = true);
	LockComponent* LockSpriteReflection(SpriteComponent* sprite);

	LockComponent* SetPositionOffset(Vector2 value);
	LockComponent* SetRotationOffset(float value);
	LockComponent* SetScaleOffset(Vector2 value);

private:
	Engine::GameObject* target;

	bool lockPosition;
	bool lockRotation;
	bool lockScale;
	SpriteComponent* gameObjectSprite;
	SpriteComponent* targetSprite;

	Vector2 positionOffset;
	float rotationOffset;
	Vector2 scaleOffset;
};

