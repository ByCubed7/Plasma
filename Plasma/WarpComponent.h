// By @ByCubed7 on Twitter

#pragma once
#include "Engine/Component.h"

class WarpComponent : public Component
{
public:
	WarpComponent(std::string name = "WarpComponent");

	void Update(double delta, Engine::Scene& game) override;

	Vector2 offset;

	bool warpX;
	bool warpY;

	WarpComponent* Set(bool warpX, bool warpY);
	WarpComponent* SetOffset(Vector2 offset);
};

