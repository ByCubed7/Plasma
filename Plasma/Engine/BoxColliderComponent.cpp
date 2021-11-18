#include "BoxColliderComponent.h"

BoxColliderComponent::BoxColliderComponent(GameObject* gameObject, std::string name)
    : Component(gameObject, name)
{
	bounds = AABB();
}

BoxColliderComponent* BoxColliderComponent::Bind(Game& game)
{
	game.colliders.push_back(this);
	return this;
}

BoxColliderComponent* BoxColliderComponent::SetSize(Vector2 size)
{
	bounds.lowerBound = size / -2;
	bounds.upperBound = size / 2;
	return this;
}

AABB BoxColliderComponent::GetBounds()
{
	AABB value = bounds;
	value.lowerBound += gameObject->position;
	value.upperBound += gameObject->position;
	return value;
}

void BoxColliderComponent::OnCollisionEnter()
{
	cout << gameObject->position.ToString() << " OnCollisionEnter" << endl;
}

void BoxColliderComponent::OnCollisionStay()
{
	cout << gameObject->position.ToString() << " OnCollisionStay" << endl;
}

void BoxColliderComponent::OnCollisionExit()
{
	cout << gameObject->position.ToString() << " OnCollisionExit" << endl;
}