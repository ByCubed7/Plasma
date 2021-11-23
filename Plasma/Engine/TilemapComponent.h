#pragma once

#include "Component.h"

#include "Event.h"
#include "Dispatcher.h"

class TilemapComponent : public Component
{
public:
	TilemapComponent(GameObject* gameObject, std::string name = "TilemapComponent");

	Tilemap tilemap;

	void Update(double delta, Game& game) override;
	void Draw(Renderer& renderer) override;
};