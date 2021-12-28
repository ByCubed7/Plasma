// By @ByCubed7 on Twitter

#pragma once

#include "Engine/Vector2.h"
#include "Engine/Component.h"

#include "InputDirector.h"

class PlayerInputDirector : public InputDirector
{
public:
	PlayerInputDirector(GameObject* gameObject, std::string name = "PlayerInputDirector");

	void Update(double delta, Engine::Scene& game) override;
};

