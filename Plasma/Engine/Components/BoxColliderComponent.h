// By @ByCubed7 on Twitter

#pragma once

#include "../Vector.h"
#include "../Component.h"
#include "../GameObject.h"
#include "../Scene.h"
#include "../AABB.h"
#include "../Dispatcher.h"


class BoxColliderComponent : public Engine::Component
{
public:
	Engine::GameObject* GetGameObject() { return gameObject; };

	struct OnEnterEventParams;
	struct OnStayEventParams;
	struct OnExitEventParams;

	BoxColliderComponent(Engine::GameObject* gameObject, std::string name = "BoxColliderComponent");

	AABB bounds;

	BoxColliderComponent* bind(Engine::Scene* game);
	BoxColliderComponent* setSize(Vector2 size);

	AABB getBounds();

	// Event Dispatchers
	Dispatcher<OnEnterEventParams> OnCollisionEnterEvent;
	Dispatcher<OnStayEventParams> OnCollisionStayEvent;
	Dispatcher<OnExitEventParams> OnCollisionExitEvent;

	void OnCollisionEnter();
	void OnCollisionStay();
	void OnCollisionExit();
};


struct BoxColliderComponent::OnEnterEventParams
{
	OnEnterEventParams(BoxColliderComponent* collider);
	BoxColliderComponent* collider;

	bool operator <(const OnEnterEventParams& rhs) const
	{
		return collider->gameObject->position.x < rhs.collider->gameObject->position.x;
	}
};

struct BoxColliderComponent::OnStayEventParams
{
	OnStayEventParams(BoxColliderComponent* collider);
	BoxColliderComponent* collider;

	bool operator <(const OnStayEventParams& rhs) const
	{
		return collider->gameObject->position.x < rhs.collider->gameObject->position.x;
	}
};

struct BoxColliderComponent::OnExitEventParams
{
	OnExitEventParams(BoxColliderComponent* collider);
	BoxColliderComponent* collider;

	bool operator <(const OnExitEventParams& rhs) const
	{
		return collider->gameObject->position.x < rhs.collider->gameObject->position.x;
	}
};