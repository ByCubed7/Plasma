// By @ByCubed7 on Twitter

#pragma once

#include "../Engine/AABB.h"
#include "../Engine/Vector2.h"
#include "../Engine/Component.h"
#include "../Engine/Event.h"
#include "../Engine/Dispatcher.h"
#include "../Render/Renderers.h"
#include "../Render/Texture2D.h"

class GameObject;
namespace Engine { class Scene; }
namespace Render { class Renderers; }

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