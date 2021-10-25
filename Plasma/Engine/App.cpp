#include "App.h"

#include "../Library/glad.h"
#include <GLFW/glfw3.h>

#include "Game.h"
#include "Resources.h"
#include "Settings.h"

#include <iostream>

App * App::instance = nullptr;

App::App(Settings config, Game* game)
{
	settings = config;
	this->game = game;
	instance = this;
}

int App::Run() 
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwWindowHint(GLFW_RESIZABLE, false);

	GLFWwindow* window = glfwCreateWindow(settings.screenWidth, settings.screenHeight, settings.name, nullptr, nullptr);
	glfwMakeContextCurrent(window);

	// Load OpenGL function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// - CALLBACKS
	// Why do we do it using Lambdas?? Why does it work? :Notlikethis:
	// This is almost definetly bad practice.

	auto callbackKey = [](GLFWwindow* window, int key, int scancode, int action, int mode) { return App::instance->CallbackKey(window, key, scancode, action, mode); };
	glfwSetKeyCallback(window, callbackKey);

	auto callbackCursorPosition = [](GLFWwindow* window, double xpos, double ypos) { return App::instance->CallbackCursorPosition(window, xpos, ypos); };
	glfwSetCursorPosCallback(window, callbackCursorPosition);
	
	auto callbackMouseButton = [](GLFWwindow* window, int button, int action, int mods) { return App::instance->CallbackMouseButton(window, button, action, mods); };
	glfwSetMouseButtonCallback(window, callbackMouseButton);

	auto callbackFramebuffer = [](GLFWwindow* window, int width, int height) { return App::instance->CallbackFramebuffer(window, width, height); };
	glfwSetFramebufferSizeCallback(window, callbackFramebuffer);
	//

	// Configure OpenGL
	glViewport(0, 0, settings.screenWidth, settings.screenHeight);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Init App
	game->GInit();
	game->Init();

	// Delta Time
	double deltaTime = 0.0f;
	double lastFrame = 0.0f;

	while (!glfwWindowShouldClose(window))
	{
		// Calculate delta time
		double currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		glfwPollEvents();

		// Process the User Input
		game->ProcessInput(deltaTime);

		// Update game state
		game->GUpdate(deltaTime);
		game->Update(deltaTime);

		// Check the Game state to see whether to close
		if (game->state == Game::State::CLOSING) glfwSetWindowShouldClose(window, true);

		// Render
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		game->GRender();
		game->Render();

		glfwSwapBuffers(window);
	}

	// Clear all of the loaded resources 
	Resources::Clear();

	// Terminate the OpenGL window
	glfwTerminate();

	return 0;
}

// -- Callbacks

void App::CallbackKey(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (!game->input.KeyExists(key)) return;
	if (action != GLFW_PRESS && action != GLFW_RELEASE) return;

	game->input.SetKey(key, action == GLFW_PRESS);
	//if (action == GLFW_PRESS) App.input.Pressed(key);
	//else if (action == GLFW_RELEASE) App.input.Released(key);
	
}

void App::CallbackMouseButton(GLFWwindow* window, int button, int action, int mods)
{
	if (action != GLFW_PRESS && action != GLFW_RELEASE) return;

	//if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
	game->input.SetMouseButton(button, action == GLFW_PRESS);
}

void App::CallbackCursorPosition(GLFWwindow* window, double xpos, double ypos)
{
	game->input.SetMousePosition(xpos, ypos);
}

void App::CallbackFramebuffer(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}