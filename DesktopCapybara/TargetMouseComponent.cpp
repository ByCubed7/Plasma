// By @ByCubed7 on Twitter

#include "All.h"

#include "WalkComponent.h"
#include "TargetMouseComponent.h"

#include <windows.h>

TargetMouseComponent::TargetMouseComponent(Engine::GameObject* gameObject, std::string name)
	: Component(gameObject, name)
{
	walkComponent = nullptr;
}

<<<<<<< Updated upstream
void TargetMouseComponent::Update(double time, double delta, Engine::Scene& game)
=======
void TargetMouseComponent::update(double time, double delta, Engine::Scene& game)
>>>>>>> Stashed changes
{
	walkComponent->SetTargetPosition(Engine::App::instance->input.mousePosition);
}

TargetMouseComponent* TargetMouseComponent::Bind(WalkComponent* component)
{
	walkComponent = component;
	return this;
}
