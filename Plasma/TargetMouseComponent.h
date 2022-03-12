// By @ByCubed7 on Twitter

#pragma once

#include "Core.h"

class WalkComponent;

class TargetMouseComponent : public Engine::Component
{
public:
	TargetMouseComponent(Engine::GameObject* gameObject, std::string name = "TargetMouseComponent");

	void Update(double delta, Engine::Scene& game) override;

	WalkComponent* walkComponent;

	TargetMouseComponent* Bind(WalkComponent* component);
};

