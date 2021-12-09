// By @ByCubed7 on Twitter

#pragma once

#include "Object.h"

#include "Scene.h"
#include "GameObject.h"

#include "Renderers.h"
#include "AABB.h"

class GameObject;
class Scene;

class Component : public Object
{
public:
	Component(std::string name = "Component");

	GameObject * gameObject;

	virtual void Update(double delta, Engine::Scene& game);
	virtual void Draw(Render::Renderers& renderer);
};