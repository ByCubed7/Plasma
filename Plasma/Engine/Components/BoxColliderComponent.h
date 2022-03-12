// By @ByCubed7 on Twitter

#pragma once

#include "../Component.h"
#include "../GameObject.h"
#include "../AABB.h"
#include "../Dispatcher.h"

//enum class BoxColliderComponentEventType {
//	TEST_EVENT,
//	TEST_EVENT2,
//	TEST_EVENT3
//};

// Forward declaration
struct Vector2;

namespace Engine { 
	class Scene;
	class GameObject;
}

class BoxColliderComponent : public Engine::Component
{
public:

	Engine::GameObject* GetGameObject() { return gameObject; };

	struct OnEnterEventParams;
	struct OnStayEventParams;
	struct OnExitEventParams;

	BoxColliderComponent(Engine::GameObject* gameObject, std::string name = "BoxColliderComponent");

	AABB bounds;

	BoxColliderComponent* Bind(Engine::Scene* game);
	BoxColliderComponent* SetSize(Vector2 size);

	AABB GetBounds();

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
	operator int() const;
};

struct BoxColliderComponent::OnStayEventParams
{
	OnStayEventParams(BoxColliderComponent* collider);
	BoxColliderComponent* collider;
	operator int() const;
};

struct BoxColliderComponent::OnExitEventParams
{
	OnExitEventParams(BoxColliderComponent* collider);
	BoxColliderComponent* collider;
	operator int() const;
};