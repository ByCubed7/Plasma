// By @ByCubed7 on Twitter

#pragma once

#include "Component.h"
#include "Vector2.h"

class CharacterControllerComponent : public Component
{
public:
	CharacterControllerComponent(std::string name = "CharacterControllerComponent");
	void Update(double delta, Scene& game) override;
};

