#include "Input.h"
#include "Library/Vector2.h"


// - - Keyboard - -

void Input::SetKey(int key, bool isDown)
{
	if (isDown) Pressed(key);
	else Released(key);
}

void Input::Pressed(int key) 
{
	state_keyboard[key] = true;
}

void Input::Released(int key)
{
	state_keyboard[key] = false;
}

bool Input::IsKey(int key) { return state_keyboard[key]; }
bool Input::IsKeyDown(int key) { return state_keyboard[key]; }
bool Input::IsKeyUp(int key) { return state_keyboard[key]; }

bool Input::AnyKey() { return false; }
bool Input::AnyKeyDown() { return false; }
bool Input::AnyKeyUp() { return false; }

bool Input::KeyExists(int key) 
{
	return key >= 0 && key < 1024;
}


// - - Mouse - -

void Input::SetMouseButton(int button, bool isDown)
{
	state_mouse[button] = isDown;
}

void Input::SetMousePosition(double xpos, double ypos)
{
	mousePosition = { (float)xpos, (float)ypos };
}

bool Input::IsMouseDown(int button)
{
	return state_mouse[button];
}

Vector2 Input::GetMousePosition()
{
	return mousePosition;
}
