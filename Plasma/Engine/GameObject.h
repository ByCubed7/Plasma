#pragma once

#include "../Library/glad.h"
#include <glm/glm.hpp>

#include "Object.h"
#include "Vector2.h"
#include "AABB.h"
#include "Texture.h"
#include "SpriteRenderer.h"
#include "Game.h"
#include "Component.h"

#include <list>

// Forward declaration
class Game;
class Component;

class GameObject : public Object
{
public:
	Vector2 position;
	float rotation;
	Vector2 scale;

	//*
	std::list<Component*> components;

	void AddComponent(Component *component);
	void RemoveComponent(Component *component);

	template<typename T>
	Component* GetComponent();
	//*/

	bool isSolid;
	bool destroyed;

	// Constructors
	GameObject();
	GameObject(Vector2 position, float rotation, Vector2 scale, Vector2 velocity, float angularVelocity, Texture2D sprite, glm::vec3 color);
};

