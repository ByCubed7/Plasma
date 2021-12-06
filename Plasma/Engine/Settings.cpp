// By @ByCubed7 on Twitter

#include <fstream>
#include <string>
#include <map>
#include <sstream>
#include <iostream>
#include <vector>

#include "Settings.h"

using namespace std;

GameConfig::GameConfig()
{
	LoadDefault();
}

void GameConfig::LoadDefault()
{
	screenWidth = 800;
	screenHeight = 600;
	name[0] = *"App";
}

void GameConfig::LoadFromFile()
{
	map<string, string> contents;
	ifstream settingFile("config.cfg");
	contents = mappify(settingFile);
	settingFile.close();

	// Use contents to set the settings~
}

map<string, string> GameConfig::mappify(ifstream &file)
{
	map<string, string> m;
	string key, val;

	while (getline(getline(file, key, ':') >> ws, val))
		m[key] = val;

	return m;
}