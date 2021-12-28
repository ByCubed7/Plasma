// By @ByCubed7 on Twitter

#pragma once

#include "Engine/Vector2.h"
#include "Engine/Component.h"

#include "InputDirector.h"

class AmbushGhostInputDirector : public InputDirector
{
public:
	AmbushGhostInputDirector(GameObject* gameObject, std::string name = "GuardGhostInputDirector");

	AmbushGhostInputDirector* SetTarget(GameObject* newTarget);

	void Update(double delta, Engine::Scene& game) override;

private:
	GameObject* target;
	Vector2 lastTurnPoint;
};

