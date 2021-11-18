#pragma once

#include "Component.h"

class BoxColliderComponent : public Component
{
public:
	BoxColliderComponent(GameObject* gameObject, std::string name = "BoxColliderComponent");

	AABB bounds;

	BoxColliderComponent* Bind(Game& game);
	BoxColliderComponent* SetSize(Vector2 size);

	AABB GetBounds();

	void OnCollisionEnter();
	void OnCollisionStay();
	void OnCollisionExit();
};