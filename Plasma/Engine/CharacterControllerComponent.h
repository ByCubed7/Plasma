// By @ByCubed7 on Twitter

#pragma once

#include "Component.h"
#include "Vector2.h"

class CharacterControllerComponent : public Component
{
public:
	CharacterControllerComponent(GameObject* gameObject, std::string name = "CharacterControllerComponent");
	void Update(double delta, Game& game) override;
};

