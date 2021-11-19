#include "PlayerCollisionEventManager.h"

#include "Engine/BoxColliderComponent.h"

PlayerCollisionEventManager::PlayerCollisionEventManager(GameObject* gameObject, std::string name)
    : Component(gameObject, name)
{

}

PlayerCollisionEventManager* PlayerCollisionEventManager::Bind(BoxColliderComponent* boxColliderComponent)
{
	boxColliderComponent->OnCollisionEnterEvent.subscribe(
		BoxColliderComponentEventType::TEST_EVENT,
		[this] (const Event<BoxColliderComponentEventType>& e) mutable
		{ OnEnter(e); }
	);

	boxColliderComponent->OnCollisionStayEvent.subscribe(
		BoxColliderComponentEventType::TEST_EVENT,
		[this] (const Event<BoxColliderComponentEventType>& e) mutable
		{ OnStay(e); }
	);
	
	boxColliderComponent->OnCollisionExitEvent.subscribe(
		BoxColliderComponentEventType::TEST_EVENT,
		[this] (const Event<BoxColliderComponentEventType>& e) mutable
		{ OnExit(e); }
	);
	
	return this;
}

PlayerCollisionEventManager* PlayerCollisionEventManager::UnBind()
{
	return this;
}

void PlayerCollisionEventManager::OnEnter(const Event<BoxColliderComponentEventType>& e)
{
	cout << "PlayerCollisionEventManager :: OnEnter" << endl;
}

void PlayerCollisionEventManager::OnStay(const Event<BoxColliderComponentEventType>& e)
{
	cout << "PlayerCollisionEventManager :: OnStay" << endl;
}

void PlayerCollisionEventManager::OnExit(const Event<BoxColliderComponentEventType>& e)
{
	cout << "PlayerCollisionEventManager :: OnExit" << endl;
}