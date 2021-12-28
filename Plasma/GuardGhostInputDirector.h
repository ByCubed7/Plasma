// By @ByCubed7 on Twitter

#pragma once

#include "Engine/Vector2.h"
#include "Engine/Component.h"

#include "InputDirector.h"

class GuardGhostInputDirector : public InputDirector
{
public:
	GuardGhostInputDirector(GameObject* gameObject, std::string name = "GuardGhostInputDirector");

	GuardGhostInputDirector* SetTarget(GameObject* newTarget);

	void Update(double delta, Engine::Scene& game) override;

private:
	GameObject* target;
	Vector2 lastTurnPoint;
};

