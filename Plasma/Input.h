#pragma once

// The current state of the keyboard and mouse
struct Input
{
	bool state[1024];

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

	// Keys
	const static int Key_Unknown = -1;
	const static int Key_Escape = 256;
};

