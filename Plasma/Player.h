#pragma once

#include "GameObject.h"
#include "Game.h"


class Player : public GameObject
{
	// Health, Speed, ect here
	// Constructor
	// Deconstructor

	// Update is called every frame ;)
	virtual void Update(double delta, Game& game) override;
};

