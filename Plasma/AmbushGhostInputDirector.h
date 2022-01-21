// By @ByCubed7 on Twitter

#pragma once

#include "Engine/Vector2.h"
#include "Engine/Component.h"

#include "InputDirector.h"
#include "GhostStateComponent.h"

class AmbushGhostInputDirector : public InputDirector
{
public:
	AmbushGhostInputDirector(GameObject* gameObject, std::string name = "GuardGhostInputDirector");

	AmbushGhostInputDirector* SetTarget(GameObject* newTarget);
	AmbushGhostInputDirector* SetStateComponent(GhostStateComponent* newStateComponent);

	void Update(double delta, Engine::Scene& game) override;

private:
	GameObject* target;
	GhostStateComponent* stateComponent;
	Vector2 lastTurnPoint;
};

