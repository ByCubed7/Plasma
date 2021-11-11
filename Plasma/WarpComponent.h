#pragma once
#include "Engine/Component.h"

class WarpComponent : public Component
{
public:
	WarpComponent(GameObject* gameObject, std::string name = "WarpComponent");

	void Update(double delta, Game& game) override;

	bool warpX;
	bool warpY;

	WarpComponent* Set(bool warpX, bool warpY);
};

