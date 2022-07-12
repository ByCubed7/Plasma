// By @ByCubed7 on Twitter


//#define VERBOSE

#include "CharacterControllerComponent.h"

#include "../Component.h"
#include "../GameObject.h"
#include "../Scene.h"
#include "../Vector.h"
#include "../App.h"


CharacterControllerComponent::CharacterControllerComponent(Engine::GameObject* gameObject, std::string name)
	: Component(gameObject, name)
{

}

void CharacterControllerComponent::Update(double time, double delta, Engine::Scene& game)
{
	// - Input

	Vector2 velocity = { 0,0 };

	// Velocity
	if (Engine::App::instance->input.IsKey(Input::Key_D)) velocity.x = 20.0f * game.timeStep;
	else if (Engine::App::instance->input.IsKey(Input::Key_A)) velocity.x = -20.0f * game.timeStep;
	else velocity.x = 0;

	if (Engine::App::instance->input.IsKey(Input::Key_S)) velocity.y = 20.0f * game.timeStep;
	else if (Engine::App::instance->input.IsKey(Input::Key_W)) velocity.y = -20.0f * game.timeStep;
	else velocity.y = 0;

	// Normilize velo
	if (velocity.Magnitude())
	{
		velocity.Normalize();
		velocity *= 300;
	}

	gameObject->position += velocity * (float) delta;

	// Rotation
	if (Engine::App::instance->input.IsKey(Input::Key_W)) gameObject->rotation = 270;
	if (Engine::App::instance->input.IsKey(Input::Key_A)) gameObject->rotation = 180;
	if (Engine::App::instance->input.IsKey(Input::Key_S)) gameObject->rotation = 90;
	if (Engine::App::instance->input.IsKey(Input::Key_D)) gameObject->rotation = 0;


	// - Frame

	//frameCount += delta;
	//spriteFrame = (int)frameCount;

	//std::cout << frameCount << std::endl;
	//std::cout << spriteFrame << std::endl;
}
