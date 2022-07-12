#include "CapybaraAI.h"
#include "WalkComponent.h"

#include "All.h"

CapybaraAI::CapybaraAI(Engine::GameObject* gameObject, std::string name) :
	Component(gameObject, name), FiniteStateMachine(CapybaraStates::WANDER)
{
	walkComponent = gameObject->Get<WalkComponent>();

	wanderTargetPosition = Vector2::Random(gameObject->scene->GetWindow()->GetMonitorSize());

	AddTransition(CapybaraStates::STAND, CapybaraActions::WANDERTICK, CapybaraStates::WANDER);
	AddTransition(CapybaraStates::FOLLOW, CapybaraActions::WANDERTICK, CapybaraStates::WANDER);

	//AddTransition(CapybaraStates::STAND, CapybaraActions::FOLLOWTICK, CapybaraStates::FOLLOW);

	AddTransition(CapybaraStates::WANDER, CapybaraActions::WANDERTICK, CapybaraStates::WANDER);
	AddTransition(CapybaraStates::WANDER, CapybaraActions::WANDERED, CapybaraStates::STAND);
}

void CapybaraAI::Update(double time, double delta, Engine::Scene& game)
{
	if (walkComponent == nullptr) return;

	CapybaraStates state = GetState();

	//else if (rand() % 100 == 50)
	//	ProcessEvent(CapybaraActions::FOLLOWTICK);

	if (state == STAND) 
	{
		if (rand() % 100 == 50)
			ProcessEvent(CapybaraActions::WANDERTICK);
	}

	if (state == WANDER) {
		walkComponent->SetTargetPosition(wanderTargetPosition);

		if (Vector2::Distance(gameObject->position, wanderTargetPosition) < 50) {
			ProcessEvent(WANDERED);
			Vector2Int size = gameObject->scene->GetWindow()->GetMonitorSize();
			wanderTargetPosition = Vector2::Random(size);
		}
	}

	if (state == FOLLOW) {
		walkComponent->SetTargetPosition(Engine::App::instance->input.mousePosition);

		if (Vector2::Distance(gameObject->position, Engine::App::instance->input.mousePosition) < 50) {
			
		}
	}

}

CapybaraAI* CapybaraAI::Bind(WalkComponent* component)
{
	walkComponent = component;
	return this;
}
