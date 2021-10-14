#pragma once

#include "Library/glad.h"
#include <glm/glm.hpp>

#include "texture.h"
#include "SpriteRenderer.h"
#include "Game.h"
#include "Library/Vector2.h"


// Forward declaration
class Game;

class GameObject
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

	// render state
	Texture2D sprite;

	// Constructors
	GameObject();
	GameObject(Vector2 position, float rotation, Vector2 scale, Vector2 velocity, float angularVelocity, Texture2D sprite, glm::vec3 color);
	
	// Draw
	virtual void Draw(SpriteRenderer& renderer);

	// Update is called every frame ;)
	virtual void Update(double delta, Game& game);

};

