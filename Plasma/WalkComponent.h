// By @ByCubed7 on Twitter

#pragma once

#include "Core.h"

class WalkComponent : public Engine::Component
{
public:
	WalkComponent(Engine::GameObject* gameObject, std::string name = "WalkComponent");

	void Update(double time, double delta, Engine::Scene& game) override;


	double stepCount;

	WalkComponent* SetTargetPosition(Vector2 position);
private:

	Vector2 absoluteTarget;
	Vector2 target;
	Vector2 wobble;
	float step;
};

