// By @ByCubed7 on Twitter

#include "All.h"
//#define VERBOSE

#include "Window.h"

namespace Engine {
	Window* Window::instance = nullptr;

	Window::Window(int width, int height) : Object("Window")
	{
		instance = this;
		title = "Title";

		state = State::RUNNING;

		this->width = width;
		this->height = height;

		// See: https://gist.github.com/esmitt/e722265936f0ebe96fc166bdf1fff41b

		glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
		// Set the visibility window hint to false for subsequent window creation
		glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

		// Initialize window
		window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(window); // Make the window's context 

		glfwSetWindowAttrib(window, GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		//glfwSetWindowPos(window, 0, 0);

		// Show the window
		glfwShowWindow(window);

		// Hide the border of the window
		glfwSetWindowAttrib(window, GLFW_DECORATED, GLFW_FALSE);

		// Specifies whether the windowed mode window will be resizable by the user.
		//glfwSetWindowAttrib(window, GLFW_RESIZABLE, false);
		
		
		
		// Done setting up the window, reset the window hints.
		glfwDefaultWindowHints();
		
		// - REGISTER CALLBACKS
		// This could certainly look better--

		auto callbackKey = [](GLFWwindow* window, int key, int scancode, int action, int mode)
		{ return Window::instance->GraphicsCallbackKey(window, key, scancode, action, mode); };
		glfwSetKeyCallback(window, callbackKey);

		auto callbackCursorPosition = [](GLFWwindow* window, double xpos, double ypos)
		{ return Window::instance->GraphicsCallbackCursorPosition(window, xpos, ypos); };
		glfwSetCursorPosCallback(window, callbackCursorPosition);

		auto callbackMouseButton = [](GLFWwindow* window, int button, int action, int mods)
		{ return Window::instance->GraphicsCallbackMouseButton(window, button, action, mods); };
		glfwSetMouseButtonCallback(window, callbackMouseButton);

		auto callbackFramebuffer = [](GLFWwindow* window, int width, int height)
		{ return Window::instance->GraphicsCallbackFramebuffer(window, width, height); };
		glfwSetFramebufferSizeCallback(window, callbackFramebuffer);
	}

	void Window::LoadScene(Scene* newScene)
	{
		scene = newScene;
	}

	void Window::Render()
	{
		scene->Render();
		glfwSwapBuffers(window);

		// Check the Game state to see whether to close
		if (scene->state == Scene::State::CLOSING) {
			state = State::QUITTING;
			glfwSetWindowShouldClose(window, true);
		}
	}

	void Window::Title(std::string newName)
	{
		title = newName;
		glfwSetWindowTitle(window, title.c_str());
	}

	void Window::Resize(int newWidth, int newHeight)
	{
		width = newWidth;
		height = newHeight;
		glfwSetWindowSize(window, width, height);
	}

	//

	void Window::GraphicsCallbackKey(GLFWwindow* window, int key, int scancode, int action, int mode)
	{
		if (!scene->input.KeyExists(key)) return;
		if (action != GLFW_PRESS && action != GLFW_RELEASE) return;

		scene->input.SetKey(key, action == GLFW_PRESS);
		//if (action == GLFW_PRESS) App.input.Pressed(key);
		//else if (action == GLFW_RELEASE) App.input.Released(key);

	}

	void Window::GraphicsCallbackMouseButton(GLFWwindow* window, int button, int action, int mods)
	{
		if (action != GLFW_PRESS && action != GLFW_RELEASE) return;

		//if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
		scene->input.SetMouseButton(button, action == GLFW_PRESS);
	}

	void Window::GraphicsCallbackCursorPosition(GLFWwindow* window, double xpos, double ypos)
	{
		scene->input.SetMousePosition(xpos, ypos);
	}

	void Window::GraphicsCallbackFramebuffer(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}
}