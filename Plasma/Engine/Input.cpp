// By @ByCubed7 on Twitter


//#define VERBOSE

#include "Input.h"
#include "Vector.h"

#include <unordered_set>

#include <windows.h> // GetAsyncKeyState


void Input::Update()
{
	for (Key i = 0; i < keyboardBufferSize; i++) {
		if (state_keyboard_frame.contains(i)) continue;
		bool pressed = GetAsyncKeyState(i);

		if (pressed ^ state_keyboard[i])
			SetKey(i, pressed);
	}
}

void Input::Clear()
{
	state_keyboard_frame.clear();
}


// - - Keyboard

void Input::SetKey(Key key, bool value)
{
	if (value) Pressed(key);
	else Released(key);
}

void Input::Pressed(Key key)
{
	state_keyboard[key] = true;
	state_keyboard_frame.insert(key);
}

void Input::Released(Key key)
{
	state_keyboard[key] = false;
	state_keyboard_frame.insert(key);
}

//

// Is the given key pressed?
bool Input::IsKey(Key key) { return state_keyboard[key]; }

// Was the given key pressed on this frame?
bool Input::IsKeyDown(Key key) {
	bool keyUpdated = state_keyboard_frame.find(key) != state_keyboard_frame.end();
	return state_keyboard[key] && keyUpdated;
}

// Was the given key unpressed on this frame?
bool Input::IsKeyUp(Key key) {
	bool keyUpdated = state_keyboard_frame.find(key) != state_keyboard_frame.end();
	return !state_keyboard[key] && keyUpdated;
}

bool Input::AnyKey() { return false; }
bool Input::AnyKeyDown() { return false; }
bool Input::AnyKeyUp() { return false; }

bool Input::KeyExists(Key key)
{
	return key >= 0 && key < 1024;
}


// - - Mouse

void Input::SetMouseButton(Button button, bool value)
{
	state_mouse[button] = value;
}

void Input::SetMousePosition(double xpos, double ypos)
{
	mousePosition = { (float)xpos, (float)ypos };
}

bool Input::IsMouseDown(Button button)
{
	return state_mouse[button];
}

Vector2 Input::GetMousePosition()
{
	return mousePosition;
}
