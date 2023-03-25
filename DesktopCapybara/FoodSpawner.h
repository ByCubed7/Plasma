#pragma once

#include "All.h"

class FoodSpawner : public Engine::Component
{
public:
	FoodSpawner(Engine::GameObject* gameObject, std::string name = "FoodSpawnerComponent");

	void Update(double time, double delta, Engine::Scene& game) override;
};

