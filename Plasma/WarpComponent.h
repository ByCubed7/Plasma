// By @ByCubed7 on Twitter

#pragma once

#include "Core.h"

class WarpComponent : public Engine::Component
{
public:
	WarpComponent(Engine::GameObject* gameObject, std::string name = "WarpComponent");

	void Update(double delta, Engine::Scene& game) override;

	Vector2 offset;

	bool warpX;
	bool warpY;

	WarpComponent* Set(bool warpX, bool warpY);
	WarpComponent* SetOffset(Vector2 offset);
};

