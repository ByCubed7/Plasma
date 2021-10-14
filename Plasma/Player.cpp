#include "Library/Vector2.h"
#include "Player.h"
//#include "Game.h"


void Player::Update(double delta, Game& game)
{
	// Get the input
	if (game.input.IsKeyDown(Input::Key_D)) velocity.x = 20.0f;
	else if (game.input.IsKeyDown(Input::Key_A)) velocity.x = -20.0f;
	else velocity.x = 0;

	if (game.input.IsKeyDown(Input::Key_S)) velocity.y = 20.0f;
	else if (game.input.IsKeyDown(Input::Key_W)) velocity.y = -20.0f;
	else velocity.y = 0;

	// Normilize velo
	if (velocity.Magnitude()) 
	{
		velocity.Normalize();
		velocity = velocity * 300;
	}
}