// By @ByCubed7 on Twitter

#pragma once

#include "Object.h"
#include "Vector2.h"
#include "Scene.h"

#include "glad.h"
#include <glm/glm.hpp>

#include <list>

// Forward declaration
class Component;
namespace Engine { class Scene; }

class GameObject : public Object
{
public:
	Engine::Scene* scene;

	Vector2 position;
	float rotation;
	Vector2 scale;

	//*
	std::list<Component*> components;

	Component* AddComponent(Component* component);
	Component* GetComponent(std::string componentName);
	bool HasComponent(std::string componentName);
	void RemoveComponent(Component *component);

	//*/

	bool isSolid;
	bool destroyed;

	// Constructors
	GameObject(Engine::Scene* scene);
	//GameObject(Vector2 position, float rotation, Vector2 scale, Vector2 velocity, float angularVelocity, Texture2D sprite, glm::vec3 color);

	// Operator Overrides
	operator bool();
};

