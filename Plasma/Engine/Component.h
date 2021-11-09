#pragma once

#include "Object.h"
#include "GameObject.h"
#include "Renderer.h"
#include "Game.h"

class GameObject;
class Game;

class Component : Object
{
public:
	Component(GameObject* gameObject, std::string name = "Component");

	GameObject * gameObject;

	virtual void Update(double delta, Game& game);
	virtual void Draw(Renderer& renderer);
};