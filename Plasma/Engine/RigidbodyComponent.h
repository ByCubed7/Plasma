#pragma once

#include "Object.h"
#include "Renderer.h"
#include "GameObject.h"
#include "Game.h"
#include "Component.h"

class RigidbodyComponent : public Component
{
public:
	RigidbodyComponent(GameObject* gameObject, std::string name = "RigidbodyComponent");

	void Update(double delta, Game& game) override;

	Vector2 velocity;
	float angularVelocity;
};