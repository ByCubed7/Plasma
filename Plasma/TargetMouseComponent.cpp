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

void TargetMouseComponent::Update(double time, double delta, Engine::Scene& game)
{
	walkComponent->SetTargetPosition(gameObject->scene->input.mousePosition);
}

TargetMouseComponent* TargetMouseComponent::Bind(WalkComponent* component)
{
	walkComponent = component;
	return this;
}
