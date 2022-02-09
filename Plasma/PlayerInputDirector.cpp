// By @ByCubed7 on Twitter

#include "All.h"

#include "PlayerInputDirector.h"

PlayerInputDirector::PlayerInputDirector(GameObject* gameObject, std::string name)
	: InputDirector(gameObject, name)
{}

void PlayerInputDirector::Update(double delta, Engine::Scene & game)
{
	if		(game.input.IsKey(Input::Key_W)) inputDirection = {  0,-1 };
	else if (game.input.IsKey(Input::Key_A)) inputDirection = { -1, 0 };
	else if (game.input.IsKey(Input::Key_S)) inputDirection = {  0, 1 };
	else if (game.input.IsKey(Input::Key_D)) inputDirection = {  1, 0 };

	PassInputDirection();
}
