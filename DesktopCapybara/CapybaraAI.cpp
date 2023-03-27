#include "CapybaraAI.h"

CapybaraAI::CapybaraAI(Engine::GameObject* gameObject, std::string name) :
	Component(gameObject, name), FiniteStateMachine(CapybaraStates::WANDER)
{
	walkComponent = gameObject->getComponent<WalkComponent>();

	wanderTargetPosition = Vector2::random((Vector2)gameObject->scene->app->getSize().Cast<Vector2>());

	AddTransition(CapybaraStates::STAND, CapybaraActions::WANDERTICK, CapybaraStates::WANDER);
	AddTransition(CapybaraStates::FOLLOW, CapybaraActions::WANDERTICK, CapybaraStates::WANDER);

	//AddTransition(CapybaraStates::STAND, CapybaraActions::FOLLOWTICK, CapybaraStates::FOLLOW);

	AddTransition(CapybaraStates::WANDER, CapybaraActions::WANDERTICK, CapybaraStates::WANDER);
	AddTransition(CapybaraStates::WANDER, CapybaraActions::WANDERED, CapybaraStates::STAND);
}

void CapybaraAI::update(double time, double delta, Engine::Scene& game)
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

		if (Vector2::distance(gameObject->position, wanderTargetPosition) < 50) {
			ProcessEvent(WANDERED);
			Vector2Int size = gameObject->scene->app->getSize();
			wanderTargetPosition = Vector2::random(size.Cast<Vector2>());
		}
	}

	if (state == FOLLOW) {
		walkComponent->SetTargetPosition(Engine::App::instance->input.mousePosition);

		if (Vector2::distance(gameObject->position, Engine::App::instance->input.mousePosition) < 50) {
			
		}
	}

}

CapybaraAI* CapybaraAI::Bind(WalkComponent* component)
{
	walkComponent = component;
	return this;
}
