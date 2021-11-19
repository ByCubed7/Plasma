#pragma once

#include "Engine/Component.h"
#include "Engine/BoxColliderComponent.h"

class PlayerCollisionEventManager : public Component
{
public:
	PlayerCollisionEventManager(GameObject* gameObject, std::string name = "PlayerCollisionEventManager");

	PlayerCollisionEventManager* Bind(BoxColliderComponent* boxColliderComponent);
	PlayerCollisionEventManager* UnBind();

private:
	void OnEnter(const Event<BoxColliderComponentEventType>& e);
	void OnStay(const Event<BoxColliderComponentEventType>& e);
	void OnExit(const Event<BoxColliderComponentEventType>& e);
};
