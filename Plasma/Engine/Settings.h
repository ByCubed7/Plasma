// By @ByCubed7 on Twitter

#pragma once

#include <fstream>
#include <string>
#include <map>
#include <sstream>
#include <iostream>
#include <vector>

struct Settings
{
	// - Constructors
	Settings();

	// Loads default settings
	void LoadDefault();

	// Loads settings from file
	void LoadFromFile();

	// The width of the screen
	// Unsigned due to never being negative
	unsigned int screenWidth = 800;
	
	// The height of the screen
	// Unsigned due to never being negative
	unsigned int screenHeight = 600;

	// The application name for the window
	char name[4] = "App";

	// Pixels per unit
	static const int PPU = 50;

private:
	std::map<std::string, std::string> mappify(std::ifstream& file);
};

