#pragma once

#include "All.h"

class FoodSpawner : public Engine::Component
{
public:
	FoodSpawner(Engine::GameObject* gameObject, std::string name = "FoodSpawnerComponent");

<<<<<<< Updated upstream
	void Update(double time, double delta, Engine::Scene& game) override;
=======
	void update(double time, double delta, Engine::Scene& game) override;
>>>>>>> Stashed changes
};

