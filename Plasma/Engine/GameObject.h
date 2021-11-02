#pragma once

#include "../Library/glad.h"
#include <glm/glm.hpp>

#include "Object.h"
#include "Vector2.h"
#include "AABB.h"
#include "Texture.h"
#include "SpriteRenderer.h"
#include "Game.h"

// Forward declaration
class Game;

class GameObject : Object
{
public:
	Vector2 position;
	float rotation;
	Vector2 scale;

	Vector2 velocity;
	float angularVelocity;

	glm::vec3 color;
	bool isSolid;
	bool destroyed;

	// Render state
	Texture2D sprite;
	void SetSprite(Texture2D sprite);
	Texture2D GetSprite();

	int spriteFrame;
	int spriteSize;

	// Bounds
	AABB bounds;
	AABB GetBounds();
	void CalcBounds();

	// Constructors
	GameObject();
	GameObject(Vector2 position, float rotation, Vector2 scale, Vector2 velocity, float angularVelocity, Texture2D sprite, glm::vec3 color);
	
	// Draw
	virtual void Draw(SpriteRenderer& renderer);

	// Update is called every frame ;)
	virtual void Update(double delta, Game& game);

	//virtual string ToString() override;
};

