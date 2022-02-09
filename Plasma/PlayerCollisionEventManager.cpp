// By @ByCubed7 on Twitter

#include "All.h"

#include "PlayerCollisionEventManager.h"
#include "GhostStateComponent.h"

PlayerCollisionEventManager::PlayerCollisionEventManager(GameObject* gameObject, std::string name)
    : Component(gameObject, name)
{

}

PlayerCollisionEventManager* PlayerCollisionEventManager::Subscribe(BoxColliderComponent* boxColliderComponent)
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

PlayerCollisionEventManager* PlayerCollisionEventManager::UnSubscribe()
{
	std::cerr << "[PlayerCollisionEventManager::UnSubscribe]\tUnSubscribe has not been implemented yet." << std::endl;
	return this;
}

void PlayerCollisionEventManager::OnEnter(const Event<BoxColliderComponent::OnEnterEventParams>& e)
{
	std::cout << "PlayerCollisionEventManager :: OnEnter  " 
		<< e.type().collider->gameObject->position.ToString() 
		<< e.type().collider->gameObject->ToString()
		<< std::endl;

	GhostStateComponent* ghostState = (GhostStateComponent*)e.type().collider->gameObject->GetComponent("GhostStateComponent");
	if (ghostState->IsFrightened()) ghostState->Kill();
	else if (ghostState->state != GhostState::DEAD)
		; // kill pacman
}

void PlayerCollisionEventManager::OnStay(const Event<BoxColliderComponent::OnStayEventParams>& e)
{
	//std::cout << "PlayerCollisionEventManager :: OnStay" << std::endl;
}

void PlayerCollisionEventManager::OnExit(const Event<BoxColliderComponent::OnExitEventParams>& e)
{
	//std::cout << "PlayerCollisionEventManager :: OnExit" << std::endl;
}
