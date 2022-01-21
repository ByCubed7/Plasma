// By @ByCubed7 on Twitter

#pragma once

#include "Engine/Component.h"
#include "Engine/BoxColliderComponent.h"

class PlayerCollisionEventManager : public Component
{
public:
	PlayerCollisionEventManager(GameObject* gameObject, std::string name = "PlayerCollisionEventManager");

	PlayerCollisionEventManager* Subscribe(BoxColliderComponent* boxColliderComponent);
	PlayerCollisionEventManager* UnSubscribe();

private:
	void OnEnter(const Event<BoxColliderComponent::OnEnterEventParams>& e);
	void OnStay(const Event<BoxColliderComponent::OnStayEventParams>& e);
	void OnExit(const Event<BoxColliderComponent::OnExitEventParams>& e);
};
