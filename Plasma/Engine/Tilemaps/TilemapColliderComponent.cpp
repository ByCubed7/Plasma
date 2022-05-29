// By @ByCubed7 on Twitter


//#define VERBOSE

#include "TilemapColliderComponent.h"

#include "../GameObject.h"
#include "../Scene.h"

TilemapColliderComponent::TilemapColliderComponent(Engine::GameObject* gameObject, std::string name)
	: Component(gameObject, name)
{
}

TilemapColliderComponent* TilemapColliderComponent::Bind(Engine::Scene* game)
{
	//game->colliders.push_back(this);
	return this;
}

TilemapColliderComponent* TilemapColliderComponent::SetTilemap(Tilemaps::Tilemap tilemap)
{
	this->tilemap = tilemap;
	return this;
}


void TilemapColliderComponent::OnCollisionEnter()
{
	Event<TilemapColliderComponent::OnEnterEventParams> e(this);
	OnCollisionEnterEvent.Invoke(e);
}

void TilemapColliderComponent::OnCollisionStay()
{
	Event<TilemapColliderComponent::OnStayEventParams> e(this);
	OnCollisionStayEvent.Invoke(e);
}

void TilemapColliderComponent::OnCollisionExit()
{
	Event<TilemapColliderComponent::OnExitEventParams> e(this);
	OnCollisionExitEvent.Invoke(e);
}


TilemapColliderComponent::OnEnterEventParams::OnEnterEventParams(TilemapColliderComponent* collider)
{ this->collider = collider; }

TilemapColliderComponent::OnStayEventParams::OnStayEventParams(TilemapColliderComponent* collider)
{ this->collider = collider; }

TilemapColliderComponent::OnExitEventParams::OnExitEventParams(TilemapColliderComponent* collider)
{ this->collider = collider; }

TilemapColliderComponent::OnEnterEventParams::operator int() const { return (int)collider->gameObject->position.x; }
TilemapColliderComponent::OnStayEventParams::operator int() const { return (int)collider->gameObject->position.x; }
TilemapColliderComponent::OnExitEventParams::operator int() const { return (int)collider->gameObject->position.x; }