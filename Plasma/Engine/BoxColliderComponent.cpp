#include "BoxColliderComponent.h"

BoxColliderComponent::BoxColliderComponent(GameObject* gameObject, std::string name)
    : Component(gameObject, name)
{
	bounds = AABB();
}

void BoxColliderComponent::Bind(Game& game)
{
	game.colliders.push_back(this);
}