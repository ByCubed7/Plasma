// By @ByCubed7 on Twitter

#pragma once

#include <string>

struct Settings
{
	// - Constructors
	Settings();

	// Loads settings from file
	void LoadFromFile();

	// The width of the screen
	// Unsigned due to never being negative
	unsigned int screenWidth = 800;
	
	// The height of the screen
	// Unsigned due to never being negative
	unsigned int screenHeight = 600;

	// The application name for the window
	std::string name = "App";

	// Pixels per unit
	int PPU = 32;

	int HalfWidth();
	int HalfHeight();
};

