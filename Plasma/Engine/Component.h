#pragma once

#include "GameObject.h"
#include "Object.h"
#include "Renderer.h"
#include "Game.h"

class Component : Object
{
public:
	Component(GameObject* gameObject, std::string name = "Component");

	GameObject * gameObject;

	virtual void Update(double delta, Game& game);
	virtual void Draw(Renderer renderer);
};