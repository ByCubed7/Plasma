// By @ByCubed7 on Twitter

#include "Library/glad.h"
#include <GLFW/glfw3.h>

#include "Engine/Game.h"
#include "Engine/Resources.h"
#include "Engine/Settings.h"

#include <iostream>

#include "Engine/App.h"
#include "Pacman.h"

//void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);


// - INPUT CALLBACKS - - - - - - - - - - - - - - - - - - - - - - - - - - - 
/*
static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	App.input.SetMousePosition(xpos, ypos);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (!App.input.KeyExists(key)) return;
	if (action != GLFW_PRESS && action != GLFW_RELEASE) return;

	App.input.SetKey(key, action == GLFW_PRESS);
	//if (action == GLFW_PRESS) App.input.Pressed(key);
	//else if (action == GLFW_RELEASE) App.input.Released(key);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (action != GLFW_PRESS && action != GLFW_RELEASE) return;
	
	//if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
	App.input.SetMouseButton(button, action == GLFW_PRESS);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
*/

// MAIN

int main(int argc, char* argv[])
{
	Settings config;

	config.screenHeight = 31*32;
	config.screenWidth = 28*32;

	Pacman pacman(config);

	App app(config, &pacman);
	return app.Run();
}