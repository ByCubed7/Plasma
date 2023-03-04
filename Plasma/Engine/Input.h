// By @ByCubed7 on Twitter

#pragma once

#include "Vector.h"
#include <unordered_set>

// The current state of the keyboard and mouse
struct Input
{
	typedef unsigned int Key;
	typedef unsigned int Button;

private:
	static const Key keyboardBufferSize = 256;
	static const Button mouseBufferSize = 8;

public:
	void Update();
	void Clear();
	
	// Keyboard
	bool state_keyboard[keyboardBufferSize];
	std::unordered_set<Key> state_keyboard_frame;

	void SetKey(Key key, bool value);
	void Pressed(Key key);
	void Released(Key key);

	bool IsKey(Key key);
	bool IsKeyDown(Key key);
	bool IsKeyUp(Key key);

	bool AnyKey();
	bool AnyKeyDown();
	bool AnyKeyUp();

	bool KeyExists(Key key);

	// Keyboard consts
	//const static int Key_Unknown = -1;

	const static Key Key_Escape = 256;
	const static Key Key_W = 87;
	const static Key Key_A = 65;
	const static Key Key_D = 68;
	const static Key Key_S = 83;
	const static Key Key_P = 80;
	// See: https://www.glfw.org/docs/3.3/group__keys.html


	// Mouse
	bool state_mouse[mouseBufferSize];
	Vector2 mousePosition = {0, 0};

	void SetMouseButton(Button button, bool value);
	void SetMousePosition(double xpos, double ypos);

	bool IsMouseDown(Button button);
	Vector2 GetMousePosition();


};

