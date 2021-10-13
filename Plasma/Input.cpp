#include "Input.h"

void Input::SetKey(int key, bool isDown)
{
	if (isDown) Pressed(key);
	else Released(key);
}

void Input::Pressed(int key) 
{
	state[key] = true;
}

void Input::Released(int key)
{
	state[key] = false;
}

bool Input::IsKey(int key) { return state[key]; }
bool Input::IsKeyDown(int key) { return state[key]; }
bool Input::IsKeyUp(int key) { return state[key]; }

bool Input::AnyKey() { return false; }
bool Input::AnyKeyDown() { return false; }
bool Input::AnyKeyUp() { return false; }

bool Input::KeyExists(int key) 
{
	return key >= 0 && key < 1024;
}