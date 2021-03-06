// By @ByCubed7 on Twitter

#pragma once

#include "Core.h"

class WalkComponent;


enum CapybaraStates {
	AAAAAAA, WANDER, STAND, FOLLOW, OFFSCREEN, EATING
};

enum CapybaraActions {
	WANDERTICK, FOLLOWTICK, CLICK, WANDERED, OFFSCREENED, DRAGGING, SEEFOOD, ONFOOD
};

class CapybaraAI : public Engine::Component, FiniteStateMachine<CapybaraStates, CapybaraActions>
{
public:
	CapybaraAI(Engine::GameObject* gameObject, std::string name = "CapybaraAIComponent");

	void Update(double time, double delta, Engine::Scene& game) override;

	WalkComponent* walkComponent;

	CapybaraAI* Bind(WalkComponent* component);

	Vector2 wanderTargetPosition;
};