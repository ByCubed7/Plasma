// By @ByCubed7 on Twitter

#pragma once

#include "Engine/Tilemaps/Tilemap.h"

#include "Core.h"
#include "Components.h"

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

