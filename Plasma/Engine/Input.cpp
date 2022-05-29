// By @ByCubed7 on Twitter


//#define VERBOSE

#include "Input.h"
#include "Vector.h"

#include <unordered_set>

void Input::Tick() 
{
	state_keyboard_frame.clear();
}

// - - Keyboard - -

void Input::SetKey(int key, bool isDown)
{
	if (isDown) Pressed(key);
	else Released(key);
}

void Input::Pressed(int key) 
{
	state_keyboard[key] = true;
	state_keyboard_frame.insert(key);
}

void Input::Released(int key)
{
	state_keyboard[key] = false;
	state_keyboard_frame.insert(key);
}

//

// Is the given key pressed?
bool Input::IsKey(int key) { return state_keyboard[key]; }

// Was the given key pressed on this frame?
bool Input::IsKeyDown(int key) { 
	bool keyUpdated = state_keyboard_frame.find(key) != state_keyboard_frame.end();
	return state_keyboard[key] && keyUpdated;
}

// Was the given key unpressed on this frame?
bool Input::IsKeyUp(int key) { 
	bool keyUpdated = state_keyboard_frame.find(key) != state_keyboard_frame.end();
	return !state_keyboard[key] && keyUpdated;
}

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
