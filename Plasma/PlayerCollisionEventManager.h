// By @ByCubed7 on Twitter

#pragma once

#include "Engine/Component.h"
#include "Engine/BoxColliderComponent.h"

class PlayerCollisionEventManager : public Component
{
public:
	PlayerCollisionEventManager(std::string name = "PlayerCollisionEventManager");

	PlayerCollisionEventManager* Bind(BoxColliderComponent* boxColliderComponent);
	PlayerCollisionEventManager* UnBind();

private:
	void OnEnter(const Event<BoxColliderComponent::OnEnterEventParams>& e);
	void OnStay(const Event<BoxColliderComponent::OnStayEventParams>& e);
	void OnExit(const Event<BoxColliderComponent::OnExitEventParams>& e);
};
