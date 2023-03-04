// By @ByCubed7 on Twitter

#pragma once

#include "../Component.h"
#include "../AABB.h"
#include "../Render/Texture2D.h"

namespace Engine { class Scene; class GameObject; }
namespace Render { struct Renderers; }

class SpriteComponent : public Engine::Component
{
public:
	SpriteComponent(Engine::GameObject* gameObject, std::string name = "SpriteComponent");

	void Update(double time, double delta, Engine::Scene& game) override;
	void Draw(Render::Renderers& renderer) override;

	Colour4 color;

	Texture2D sprite;
	Vector2 pivot;
	bool reflectionX;
	bool reflectionY;
	Vector2Int crop;
	Vector2UInt size;

	// Set the texture
	SpriteComponent* Set(Texture2D newSprite);

	// Get the texture
	Texture2D Get();

	// Set the animation speed
	SpriteComponent* SetColour(Colour4 newColour);

	// Bounds
	AABB bounds;
	AABB GetBounds();
	void CalcBounds();

};