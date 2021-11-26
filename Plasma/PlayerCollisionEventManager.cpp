// By @ByCubed7 on Twitter

#include "PlayerCollisionEventManager.h"

#include "Engine/BoxColliderComponent.h"

PlayerCollisionEventManager::PlayerCollisionEventManager(GameObject* gameObject, std::string name)
    : Component(gameObject, name)
{

}

PlayerCollisionEventManager* PlayerCollisionEventManager::Bind(BoxColliderComponent* boxColliderComponent)
{
	boxColliderComponent->OnCollisionEnterEvent.subscribe(
		{ boxColliderComponent },
		[this] (const Event<BoxColliderComponent::OnEnterEventParams>& e)
		{ OnEnter(e); }
	);

	boxColliderComponent->OnCollisionStayEvent.subscribe(
		{ boxColliderComponent },
		[this] (const Event<BoxColliderComponent::OnStayEventParams>& e)
		{ OnStay(e); }
	);
	
	boxColliderComponent->OnCollisionExitEvent.subscribe(
		{ boxColliderComponent },
		[this] (const Event<BoxColliderComponent::OnExitEventParams>& e)
		{ OnExit(e); }
	);
	
	return this;
}

PlayerCollisionEventManager* PlayerCollisionEventManager::UnBind()
{
	return this;
}

void PlayerCollisionEventManager::OnEnter(const Event<BoxColliderComponent::OnEnterEventParams>& e)
{
	//cout << "PlayerCollisionEventManager :: OnEnter" << endl;
}

void PlayerCollisionEventManager::OnStay(const Event<BoxColliderComponent::OnStayEventParams>& e)
{
	//cout << "PlayerCollisionEventManager :: OnStay" << endl;
}

void PlayerCollisionEventManager::OnExit(const Event<BoxColliderComponent::OnExitEventParams>& e)
{
	//cout << "PlayerCollisionEventManager :: OnExit" << endl;
}