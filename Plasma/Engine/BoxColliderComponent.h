#pragma once

#include "Component.h"

#include "Event.h"
#include "Dispatcher.h"

enum class BoxColliderComponentEventType {
	TEST_EVENT,
	TEST_EVENT2,
	TEST_EVENT3
};

class BoxColliderComponent : public Component
{
public:
	struct OnEnterEventParams;
	struct OnStayEventParams;
	struct OnExitEventParams;

	BoxColliderComponent(GameObject* gameObject, std::string name = "BoxColliderComponent");

	AABB bounds;

	BoxColliderComponent* Bind(Game& game);
	BoxColliderComponent* SetSize(Vector2 size);

	AABB GetBounds();

	void OnCollisionEnter();
	void OnCollisionStay();
	void OnCollisionExit();

	// Event Dispatchers
	Dispatcher<OnEnterEventParams> OnCollisionEnterEvent;
	Dispatcher<OnStayEventParams> OnCollisionStayEvent;
	Dispatcher<OnExitEventParams> OnCollisionExitEvent;
};


struct BoxColliderComponent::OnEnterEventParams
{
	OnEnterEventParams(BoxColliderComponent* collider);
	BoxColliderComponent* collider;

	operator int() const { return collider->gameObject->position.x; }
};

struct BoxColliderComponent::OnStayEventParams
{
	OnStayEventParams(BoxColliderComponent* collider);
	BoxColliderComponent* collider;

	operator int() const { return collider->gameObject->position.x; }
};

struct BoxColliderComponent::OnExitEventParams
{
	OnExitEventParams(BoxColliderComponent* collider);
	BoxColliderComponent* collider;

	operator int() const { return collider->gameObject->position.x; }
};