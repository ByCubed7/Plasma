#pragma once

#include "Object.h"
#include "Renderer.h"
#include "GameObject.h"
#include "Game.h"
#include "Component.h"

class SpriteComponent : public Component
{
public:
	SpriteComponent(GameObject* gameObject, std::string name = "SpriteComponent");

	void Draw(Renderer& renderer) override;
	void Update(double delta, Game& game);

	glm::vec3 color;

	double animationPoint;
	int animationSpeed;

	Texture2D sprite;
	int spriteFrame;
	int spriteSize;

	// Set the texture
	// Returns self for method chaining
	SpriteComponent* Set(Texture2D sprite);

	// Get the texture
	Texture2D Get();

	// Set the animation speed
	// Returns self for method chaining
	SpriteComponent* AnimationSpeed(double speed);

	// Get the Animation speed
	int GetAnimationSpeed();

	// Bounds
	AABB bounds;
	AABB GetBounds();
	void CalcBounds();
};