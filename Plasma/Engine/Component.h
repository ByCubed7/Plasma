// By @ByCubed7 on Twitter

#pragma once

#include "Object.h"
#include "GameObject.h"
#include "Component.h"

class Component : public Object
{
public:
	Component(GameObject* gameObject, std::string name = "Component");


	GameObject * gameObject;
	Engine::Scene * scene;

	virtual void Update(double delta, Engine::Scene& game);
	virtual void Draw(Render::Renderers& renderer);
};