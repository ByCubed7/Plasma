// By @ByCubed7 on Twitter

#pragma once

#include "Object.h"

#include "Game.h"
#include "GameObject.h"

#include "Renderers.h"
#include "AABB.h"

class GameObject;
class Game;

class Component : public Object
{
public:
	Component(GameObject* gameObject, std::string name = "Component");

	GameObject * gameObject;

	virtual void Update(double delta, Game& game);
	virtual void Draw(Render::Renderers& renderer);
};