#pragma once

// The current state of the keyboard and mouse
struct Input
{

	// Keyboard
	bool state_keyboard[1024];

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
	double mousePositionX = 0;
	double mousePositionY = 0;

	void SetMouseButton(int button, bool isDown);
	void SetMousePosition(double xpos, double ypos);

	bool IsMouseDown(int button);


	// Keyboard consts
	const static int Key_Unknown = -1;
	const static int Key_Escape = 256;
	const static int Key_W = 87;
	const static int Key_A = 65;
	const static int Key_D = 68;
	const static int Key_S = 83;
	// See: https://www.glfw.org/docs/3.3/group__keys.html


};

