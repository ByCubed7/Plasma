// By @ByCubed7 on Twitter

#pragma once

#include "../Library/glad.h"
#include <GLFW/glfw3.h>

#include "Game.h"
#include "Settings.h"
#include "Resources.h"

#include <iostream>

class App
{
public:
	App(Settings config, Game* game);

	int Run();

	static App* instance;

private:

	Game* game;
	Settings settings;

	void CallbackKey(GLFWwindow* window, int key, int scancode, int action, int mode);
	void CallbackMouseButton(GLFWwindow* window, int button, int action, int mods);
	void CallbackCursorPosition(GLFWwindow* window, double xpos, double ypos);
	void CallbackFramebuffer(GLFWwindow* window, int width, int height);
	void CallbackException(GLenum source, GLenum type, unsigned int id, GLenum severity, GLsizei length, const char* message, const void* userParam);
};

