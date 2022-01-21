// By @ByCubed7 on Twitter

#pragma once

#include "Engine/Vector2.h"
#include "Engine/Component.h"

#include "InputDirector.h"
#include "GhostStateComponent.h"

class GuardGhostInputDirector : public InputDirector
{
public:
	GuardGhostInputDirector(GameObject* gameObject, std::string name = "GuardGhostInputDirector");


	GuardGhostInputDirector* SetTarget(GameObject* newTarget);
	GuardGhostInputDirector* SetStateComponent(GhostStateComponent* newStateComponent);

	void Update(double delta, Engine::Scene& game) override;

private:
	GameObject* target;
	GhostStateComponent* stateComponent;
	Vector2 lastTurnPoint;
};

