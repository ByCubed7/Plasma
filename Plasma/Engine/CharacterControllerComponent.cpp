// By @ByCubed7 on Twitter

#include "CharacterControllerComponent.h"


CharacterControllerComponent::CharacterControllerComponent(std::string name)
	: Component(name)
{

}

void CharacterControllerComponent::Update(double delta, Scene& game)
{
	// - Input

	Vector2 velocity = { 0,0 };

	// Velocity
	if (game.input.IsKey(Input::Key_D)) velocity.x = 20.0f * game.timeStep;
	else if (game.input.IsKey(Input::Key_A)) velocity.x = -20.0f * game.timeStep;
	else velocity.x = 0;

	if (game.input.IsKey(Input::Key_S)) velocity.y = 20.0f * game.timeStep;
	else if (game.input.IsKey(Input::Key_W)) velocity.y = -20.0f * game.timeStep;
	else velocity.y = 0;

	// Normilize velo
	if (velocity.Magnitude())
	{
		velocity.Normalize();
		velocity = velocity * 300;
	}

	gameObject->position += velocity * delta;

	// Rotation
	if (game.input.IsKey(Input::Key_W)) gameObject->rotation = 270;
	if (game.input.IsKey(Input::Key_A)) gameObject->rotation = 180;
	if (game.input.IsKey(Input::Key_S)) gameObject->rotation = 90;
	if (game.input.IsKey(Input::Key_D)) gameObject->rotation = 0;


	// - Frame

	//frameCount += delta;
	//spriteFrame = (int)frameCount;

	//std::cout << frameCount << std::endl;
	//std::cout << spriteFrame << std::endl;
}
