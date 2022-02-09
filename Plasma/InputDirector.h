// By @ByCubed7 on Twitter

#pragma once

#include "Core.h"

#include "TileLockedController.h"

class InputDirector : public Component
{
public:
	InputDirector(GameObject* gameObject, std::string name = "InputDirector");

	InputDirector* SetController(TileLockedController* newController);

	virtual void Update(double delta, Engine::Scene& game) override = 0;

protected:
	Vector2 inputDirection = { 0,0 };

	TileLockedController* controller;

	void PassInputDirection();
};

