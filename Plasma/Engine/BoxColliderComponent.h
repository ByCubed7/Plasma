#pragma once

#include "Component.h"

class BoxColliderComponent : public Component
{
public:
	BoxColliderComponent(GameObject* gameObject, std::string name = "BoxColliderComponent");

	AABB bounds;

	void Bind(Game& game);

	void OnCollisionEnter();
	void OnCollisionStay();
	void OnCollisionExit();
};