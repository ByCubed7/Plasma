// By @ByCubed7 on Twitter

#pragma once

#include "Vector.h"
#include <unordered_set>

// The current state of the keyboard and mouse
struct Input
{
	// Keyboard
	bool state_keyboard[1024];
	std::unordered_set<int> state_keyboard_frame;

	void Tick();

	void SetKey(int key, bool isDown);
	void Pressed(int key);
	void Released(int key);

	bool IsKey(int key);
	bool IsKeyDown(int key);
	bool IsKeyUp(int key);

	bool AnyKey();
	bool AnyKeyDown();
	bool AnyKeyUp();

	bool KeyExists(int key);

	// Mouse
	bool state_mouse[7];
	Vector2 mousePosition = {0, 0};

	void SetMouseButton(int button, bool isDown);
	void SetMousePosition(double xpos, double ypos);

	bool IsMouseDown(int button);
	Vector2 GetMousePosition();


	// Keyboard consts
	const static int Key_Unknown = -1;
	const static int Key_Escape = 256;
	const static int Key_W = 87;
	const static int Key_A = 65;
	const static int Key_D = 68;
	const static int Key_S = 83;
	const static int Key_P = 80;
	// See: https://www.glfw.org/docs/3.3/group__keys.html


};

