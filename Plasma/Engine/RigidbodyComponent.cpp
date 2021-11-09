#include "RigidbodyComponent.h"

#include "GameObject.h"
#include "Component.h"

RigidbodyComponent::RigidbodyComponent(GameObject* gameObject, std::string name)
    : Component(gameObject, name)
{
	velocity = { 0.0f, 0.0f };
	angularVelocity = 0.0f;
}

void RigidbodyComponent::Update(double delta, Game& game)
{
	gameObject->position += velocity * delta;
	gameObject->rotation += angularVelocity * delta;

	// Deal with collisions ect
}