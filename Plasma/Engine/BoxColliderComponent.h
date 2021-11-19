#pragma once

#include "Component.h"

#include "Event.h"
#include "Dispatcher.h"

enum class BoxColliderComponentEventType {
	TEST_EVENT,
	TEST_EVENT2,
	TEST_EVENT3
};

class BoxColliderComponentEvent : public Event<BoxColliderComponentEventType>
{
public:
	BoxColliderComponentEvent() : Event<BoxColliderComponentEventType>(BoxColliderComponentEventType::TEST_EVENT, "BoxColliderComponentEvent") {};
	virtual ~BoxColliderComponentEvent() = default;
};


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

	// Event Dispatchers
	Dispatcher<BoxColliderComponentEventType> OnCollisionEnterEvent;
	Dispatcher<BoxColliderComponentEventType> OnCollisionStayEvent;
	Dispatcher<BoxColliderComponentEventType> OnCollisionExitEvent;
};