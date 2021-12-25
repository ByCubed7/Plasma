// By @ByCubed7 on Twitter

#pragma once

#include "Engine/Tilemaps/Tilemap.h"

#include "Engine/Vector2.h"
#include "Engine/Component.h"
#include "Engine/TilemapComponent.h"

#include "ScoreTracker.h"

class Muncher : public Component
{
public:
	Muncher(GameObject* gameObject, std::string name = "MuncherComponent");

	TilemapComponent* tilemapComp;
	ScoreTracker* scoreTracker;

	Muncher* SetTilemap(TilemapComponent* tilemapComponent);
	Muncher* SetScore(ScoreTracker* score);

	void Update(double delta, Engine::Scene& game) override;
};

