// By @ByCubed7 on Twitter

#pragma once

#include "../Component.h"
#include "../AABB.h"
#include "../Render/Texture2D.h"

#include <glm/glm.hpp>

class GameObject;
namespace Engine { class Scene; }
namespace Render { struct Renderers; }

class SpriteComponent : public Component
{
public:
	SpriteComponent(GameObject* gameObject, std::string name = "SpriteComponent");

	void Update(double delta, Engine::Scene& game) override;
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

	// Set the animation speed
	SpriteComponent* SetColour(glm::vec3 newColour);

	// Get the Animation speed
	int GetAnimationSpeed();

	// Bounds
	AABB bounds;
	AABB GetBounds();
	void CalcBounds();
};