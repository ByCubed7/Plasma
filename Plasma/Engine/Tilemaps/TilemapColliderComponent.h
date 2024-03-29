// By @ByCubed7 on Twitter

#pragma once

#include "../Component.h"
#include "../Scene.h"
#include "../Event.h"
#include "../Dispatcher.h"

#include "Tilemap.h"

namespace Engine { class Scene; class GameObject; }

enum class TilemapColliderComponentEventType {
	TEST_EVENT,
	TEST_EVENT2,
	TEST_EVENT3
};

class TilemapColliderComponent : public Engine::Component
{
public:
	struct OnEnterEventParams;
	struct OnStayEventParams;
	struct OnExitEventParams;

	TilemapColliderComponent(Engine::GameObject* gameObject, std::string name = "TilemapColliderComponent");

	Tilemaps::Tilemap tilemap;

	TilemapColliderComponent* bind(Engine::Scene* game);
	TilemapColliderComponent* setTilemap(Tilemaps::Tilemap tilemap);

	void OnCollisionEnter();
	void OnCollisionStay();
	void OnCollisionExit();

	// Event Dispatchers
	Dispatcher<OnEnterEventParams> OnCollisionEnterEvent;
	Dispatcher<OnStayEventParams> OnCollisionStayEvent;
	Dispatcher<OnExitEventParams> OnCollisionExitEvent;
};


struct TilemapColliderComponent::OnEnterEventParams
{
	OnEnterEventParams(TilemapColliderComponent* collider);
	TilemapColliderComponent* collider;
	operator int() const;
};

struct TilemapColliderComponent::OnStayEventParams
{
	OnStayEventParams(TilemapColliderComponent* collider);
	TilemapColliderComponent* collider;
	operator int() const;
};

struct TilemapColliderComponent::OnExitEventParams
{
	OnExitEventParams(TilemapColliderComponent* collider);
	TilemapColliderComponent* collider;
	operator int() const;
};