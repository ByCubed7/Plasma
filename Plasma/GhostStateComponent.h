// By @ByCubed7 on Twitter

#pragma once

#include "Core.h"
#include "Components.h"

enum class GhostState 
{
	CHASING, // Chasing the target tile
	SCATTERING, // Each ghost has a fixed target tile it tries to reach while in scatter mode
	FRIGHTENED, // Each ghosts enter frightened mode whenever the player eats one of the four energizers.
	DEAD // Ghost returns to the center
};

class GhostStateComponent : public Component
{
public:
	GhostStateComponent(GameObject* gameObject, std::string name = "GuardGhostInputDirector");

	GhostState state;

	void Chase();
	void Scatter();
	void Frighten();
	void Kill();

	bool IsChasing();
	bool IsScattered();
	bool IsFrightened();
	bool IsDead();
};

