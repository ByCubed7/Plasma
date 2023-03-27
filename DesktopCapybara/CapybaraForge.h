#pragma once

#include "Core.h"

class CapybaraForge : public Engine::Component
{
public:
	CapybaraForge(Engine::GameObject* gameObject, std::string name = "CapybaraForgeComponent");

	void update(double time, double delta, Engine::Scene& game) override;

	Engine::GameObject* ForgeCapybara();
};

