// By @ByCubed7 on Twitter

#pragma once

#include "Engine/Tilemaps/Tilemap.h"

#include "Engine/Vector2.h"
#include "Engine/Component.h"
#include "Engine/TilemapComponent.h"

class Muncher : public Component
{
public:
	Muncher(GameObject* gameObject, std::string name = "TileLockedCharacterController");

	TilemapComponent* tilemapComp;

	Muncher* SetTilemap(TilemapComponent* tilemapComponent);

	void Update(double delta, Engine::Scene& game) override;
};

