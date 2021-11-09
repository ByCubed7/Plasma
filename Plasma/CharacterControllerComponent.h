#pragma once

#include "Engine/Component.h"
#include "Engine/Vector2.h"

class CharacterControllerComponent : public Component
{
	void Update(double delta, Game& game) override;
};

