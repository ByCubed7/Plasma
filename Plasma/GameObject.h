#pragma once

#include "Library/glad.h"
#include <glm/glm.hpp>

#include "texture.h"
#include "SpriteRenderer.h"
#include "Game.h"


// Forward declaration
class Game;

class GameObject
{
public:
	glm::vec2 position;
	float rotation;
	glm::vec2 scale;

	glm::vec2 velocity;
	float angularVelocity;

	glm::vec3 color;
	bool isSolid;
	bool destroyed;

	// render state
	Texture2D sprite;

	// Constructors
	GameObject();
	GameObject(glm::vec2 position, float rotation, glm::vec2 scale, glm::vec2 velocity, float angularVelocity, Texture2D sprite, glm::vec3 color);
	
	// Draw
	virtual void Draw(SpriteRenderer& renderer);

	// Update is called every frame ;)
	virtual void Update(double delta, Game& game);

};

