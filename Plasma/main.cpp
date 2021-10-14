#include "Library/glad.h"
#include <GLFW/glfw3.h>

#include "game.h"
#include "Resources.h"

#include <iostream>
#include "Settings.h"

// GLFW function declarations
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

Settings config;
Game App(config);

int main(int argc, char* argv[])
{

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwWindowHint(GLFW_RESIZABLE, false);

	GLFWwindow* window = glfwCreateWindow(config.screenWidth, config.screenHeight, config.name, nullptr, nullptr);
	glfwMakeContextCurrent(window);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glfwSetKeyCallback(window, key_callback);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// OpenGL configuration
	// --------------------
	glViewport(0, 0, config.screenWidth, config.screenHeight);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// initialize game
	// ---------------
	App.Init();

	// deltaTime variables
	// -------------------
	double deltaTime = 0.0f;
	double lastFrame = 0.0f;

	while (!glfwWindowShouldClose(window))
	{
		// calculate delta time
		// --------------------
		double currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		glfwPollEvents();

		// manage user input
		// -----------------
		App.ProcessInput(deltaTime);

		// update game state
		// -----------------
		App.Update(deltaTime);

		if(App.state == Game::State::CLOSING) glfwSetWindowShouldClose(window, true);

		// render
		// ------
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		App.Render();

		glfwSwapBuffers(window);
	}

	// Clear all of the loaded resources 
	Resources::Clear();

	// Terminate the OpenGL window
	glfwTerminate();
	return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (!App.input.KeyExists(key)) return;
	if (action != GLFW_PRESS && action != GLFW_RELEASE) return;

	App.input.SetKey(key, action == GLFW_PRESS);
	//if (action == GLFW_PRESS) App.input.Pressed(key);
	//else if (action == GLFW_RELEASE) App.input.Released(key);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}