// By @ByCubed7 on Twitter

#pragma once

#include "../Library/glad.h"
#include <GLFW/glfw3.h>

#include "Scene.h"
#include "Settings.h"
#include "Resources.h"

#include <iostream>

class Scene;

class App
{
public:
	App();

	Scene* CreateGame(GameConfig& gameConfig);
	//Scene* GetScene();

	int Prepare(Scene* setScene);
	int Run(Scene* setScene);

	static App* instance;


private:
	GLFWwindow* window;
	Scene* scene;
	GameConfig settings;

	void GraphicsCallbackKey(GLFWwindow* window, int key, int scancode, int action, int mode);
	void GraphicsCallbackMouseButton(GLFWwindow* window, int button, int action, int mods);
	void GraphicsCallbackCursorPosition(GLFWwindow* window, double xpos, double ypos);
	void GraphicsCallbackFramebuffer(GLFWwindow* window, int width, int height);
	void GraphicsCallbackException(GLenum source, GLenum type, unsigned int id, GLenum severity, GLsizei length, const char* message, const void* userParam);
};

