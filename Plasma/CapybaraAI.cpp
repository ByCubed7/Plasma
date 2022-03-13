#include "CapybaraAI.h"

CapybaraAI::CapybaraAI(Engine::GameObject* gameObject, std::string name) :
	Component(gameObject, name), FiniteStateMachine(CapybaraStates::STAND)
{
	AddTransition(CapybaraStates::STAND, CapybaraActions::TICK, CapybaraStates::WANDER); 
}

void CapybaraAI::Update(double delta, Engine::Scene& game)
{
}

CapybaraAI* CapybaraAI::Bind(WalkComponent* component)
{
	return this;
}
