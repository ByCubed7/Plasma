// By @ByCubed7 on Twitter

#pragma once

#include "Object.h"
#include "Renderers.h"
#include "GameObject.h"
#include "Scene.h"
#include "Component.h"

class SpriteComponent : public Component
{
public:
	SpriteComponent(std::string name = "SpriteComponent");

	void Update(double delta, Scene& game) override;
	void Draw(Render::Renderers& renderer) override;

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