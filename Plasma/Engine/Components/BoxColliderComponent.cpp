// By @ByCubed7 on Twitter


//#define VERBOSE

#include "BoxColliderComponent.h"


BoxColliderComponent::BoxColliderComponent(Engine::GameObject* gameObject, std::string name)
    : Component(gameObject, name)
{
	bounds = AABB();
}

BoxColliderComponent* BoxColliderComponent::Bind(Engine::Scene* game)
{
	game->colliders.push_back(this);
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
	AABB value = AABB(bounds);
	value.lowerBound += gameObject->position;
	value.upperBound += gameObject->position;
	return value;
}

void BoxColliderComponent::OnCollisionEnter()
{
	Event<BoxColliderComponent::OnEnterEventParams> e(this);
	OnCollisionEnterEvent.Invoke(e);
}

void BoxColliderComponent::OnCollisionStay()
{
	Event<BoxColliderComponent::OnStayEventParams> e(this);
	OnCollisionStayEvent.Invoke(e);
}

void BoxColliderComponent::OnCollisionExit()
{
	Event<BoxColliderComponent::OnExitEventParams> e(this);
	OnCollisionExitEvent.Invoke(e);
}


BoxColliderComponent::OnEnterEventParams::OnEnterEventParams(BoxColliderComponent* collider)
{ this->collider = collider; };

BoxColliderComponent::OnStayEventParams::OnStayEventParams(BoxColliderComponent* collider)
{ this->collider = collider; };

BoxColliderComponent::OnExitEventParams::OnExitEventParams(BoxColliderComponent* collider)
{ this->collider = collider; };