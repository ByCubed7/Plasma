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

	void Draw(Renderer renderer) override;

	glm::vec3 color;

	Texture2D sprite;
	int spriteFrame;
	int spriteSize;

	void Set(Texture2D sprite);
	Texture2D Get();

	// Bounds
	AABB bounds;
	AABB GetBounds();
	void CalcBounds();
};