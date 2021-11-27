// By @ByCubed7 on Twitter

#include "App.h"

#include "../Library/glad.h"
#include <GLFW/glfw3.h>

#include "Game.h"
#include "Resources.h"
#include "Settings.h"

#include <iostream>

App * App::instance = nullptr;

class Game;

App::App(Settings config, Game* game)
{
	instance = this;
	settings = config;
	this->game = game;
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
	// Why do we do it using Lambdas? This is surely bad practice.

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
	//glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	// Debugging Callback
	int flags; glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
	if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
	{
		auto callbackException = []
			(GLenum source, GLenum type, unsigned int id, GLenum severity, GLsizei length, const char* message, const void* userParam) 
			{ App::instance->CallbackException(source, type, id, severity, length, message, userParam); };

		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(callbackException, nullptr);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
	}

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

		//* Print any errors
		GLenum err;
		while ((err = glGetError()) != GL_NO_ERROR)
		{
			cout << "ERROR:" << err << endl;
		}//*/
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


void App::CallbackException(GLenum source,
	GLenum type, unsigned int id, GLenum severity, GLsizei length,
	const char* message, const void* userParam)
{
	// ignore non-significant error/warning codes
	if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

	std::cout << "---------------" << std::endl;
	std::cout << "Debug message (" << id << "): " << message << std::endl;

	switch (source)
	{
	case GL_DEBUG_SOURCE_API:             std::cout << "Source: API"; break;
	case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   std::cout << "Source: Window System"; break;
	case GL_DEBUG_SOURCE_SHADER_COMPILER: std::cout << "Source: Shader Compiler"; break;
	case GL_DEBUG_SOURCE_THIRD_PARTY:     std::cout << "Source: Third Party"; break;
	case GL_DEBUG_SOURCE_APPLICATION:     std::cout << "Source: Application"; break;
	case GL_DEBUG_SOURCE_OTHER:           std::cout << "Source: Other"; break;
	} std::cout << std::endl;

	switch (type)
	{
	case GL_DEBUG_TYPE_ERROR:               std::cout << "Type: Error"; break;
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: std::cout << "Type: Deprecated Behaviour"; break;
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  std::cout << "Type: Undefined Behaviour"; break;
	case GL_DEBUG_TYPE_PORTABILITY:         std::cout << "Type: Portability"; break;
	case GL_DEBUG_TYPE_PERFORMANCE:         std::cout << "Type: Performance"; break;
	case GL_DEBUG_TYPE_MARKER:              std::cout << "Type: Marker"; break;
	case GL_DEBUG_TYPE_PUSH_GROUP:          std::cout << "Type: Push Group"; break;
	case GL_DEBUG_TYPE_POP_GROUP:           std::cout << "Type: Pop Group"; break;
	case GL_DEBUG_TYPE_OTHER:               std::cout << "Type: Other"; break;
	} std::cout << std::endl;

	switch (severity)
	{
	case GL_DEBUG_SEVERITY_HIGH:         std::cout << "Severity: high"; break;
	case GL_DEBUG_SEVERITY_MEDIUM:       std::cout << "Severity: medium"; break;
	case GL_DEBUG_SEVERITY_LOW:          std::cout << "Severity: low"; break;
	case GL_DEBUG_SEVERITY_NOTIFICATION: std::cout << "Severity: notification"; break;
	} std::cout << std::endl;
	std::cout << std::endl;
}