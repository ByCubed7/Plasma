// By @ByCubed7 on Twitter

#pragma once

#include "Core.h"

class LockComponent : public Engine::Component
{
public:
	LockComponent(Engine::GameObject* gameObject, std::string name = "LockComponent");

	void Update(double delta, Engine::Scene& game) override;

	LockComponent* SetTarget(Engine::GameObject* target);
private:
	Engine::GameObject* target;
};

