// By @ByCubed7 on Twitter

#include "All.h"
//#define VERBOSE

#include "Settings.h"

#include <fstream>
#include <map>
#include <sstream>
#include <iostream>
#include <vector>

Settings::Settings()
{
	screenWidth = 800;
	screenHeight = 600;
	name = "App";
}

void Settings::LoadFromFile()
{
}

int Settings::HalfWidth()  { return screenWidth / 2; }
int Settings::HalfHeight() { return screenHeight / 2; }