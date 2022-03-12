// By @ByCubed7 on Twitter

#pragma once

#include "Core.h"

class WalkComponent;

class CapybaraAI : public Engine::Component
{
public:
	CapybaraAI(Engine::GameObject* gameObject, std::string name = "CapybaraAIComponent");

	void Update(double delta, Engine::Scene& game) override;

	WalkComponent* walkComponent;

	CapybaraAI* Bind(WalkComponent* component);
};

