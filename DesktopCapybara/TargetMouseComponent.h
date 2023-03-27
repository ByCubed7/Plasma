// By @ByCubed7 on Twitter

#pragma once

#include "Core.h"

class WalkComponent;

class TargetMouseComponent : public Engine::Component
{
public:
	TargetMouseComponent(Engine::GameObject* gameObject, std::string name = "TargetMouseComponent");

<<<<<<< Updated upstream
	void Update(double time, double delta, Engine::Scene& game) override;
=======
	void update(double time, double delta, Engine::Scene& game) override;
>>>>>>> Stashed changes

	WalkComponent* walkComponent;

	TargetMouseComponent* Bind(WalkComponent* component);
};

