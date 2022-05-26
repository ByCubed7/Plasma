#include "CapybaraAI.h"
#include "WalkComponent.h"

CapybaraAI::CapybaraAI(Engine::GameObject* gameObject, std::string name) :
	Component(gameObject, name), FiniteStateMachine(CapybaraStates::FOLLOW)
{
	walkComponent = nullptr;

	AddTransition(CapybaraStates::STAND, CapybaraActions::TICK, CapybaraStates::WANDER); 
	AddTransition(CapybaraStates::WANDER, CapybaraActions::WANDERED, CapybaraStates::STAND); 
}

void CapybaraAI::Update(double time, double delta, Engine::Scene& game)
{
	if (walkComponent == nullptr) return;

	switch (GetState()) {
	case STAND:
		break;
	case WANDER:

	case FOLLOW:
		walkComponent->SetTargetPosition(gameObject->scene->input.mousePosition);
		break;
	}
}

CapybaraAI* CapybaraAI::Bind(WalkComponent* component)
{
	walkComponent = component;
	return this;
}
