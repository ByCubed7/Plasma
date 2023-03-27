#pragma once

#include "All.h"

class FoodSpawner : public Engine::Component
{
public:
	FoodSpawner(Engine::GameObject* gameObject, std::string name = "FoodSpawnerComponent");

	void update(double time, double delta, Engine::Scene& game) override;
};

