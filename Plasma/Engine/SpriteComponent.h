// By @ByCubed7 on Twitter

#pragma once

#include "Object.h"
#include "Renderers.h"
#include "GameObject.h"
#include "Game.h"
#include "Component.h"

class SpriteComponent : public Component
{
public:
	SpriteComponent(GameObject* gameObject, std::string name = "SpriteComponent");

	void Update(double delta, Game& game) override;
	void Draw(Renderers& renderer) override;

	glm::vec3 color;

	double animationPoint;
	int animationSpeed;

	Texture2D sprite;
	int spriteFrame;
	int spriteSize;

	// Set the texture
	SpriteComponent* Set(Texture2D sprite);

	// Get the texture
	Texture2D Get();

	// Set the animation speed
	SpriteComponent* AnimationSpeed(double speed);

	// Get the Animation speed
	int GetAnimationSpeed();

	// Bounds
	AABB bounds;
	AABB GetBounds();
	void CalcBounds();
};