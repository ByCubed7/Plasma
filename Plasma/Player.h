#pragma once

#include "Engine/GameObject.h"
#include "Engine/Game.h"


class Player : public GameObject
{
	// Health, Speed, ect here
	// Constructor
	// Deconstructor
	double frameCount = 0;

	// Update is called every frame ;)
	virtual void Update(double delta, Game& game) override;
};

