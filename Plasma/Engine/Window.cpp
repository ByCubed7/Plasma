// By @ByCubed7 on Twitter

#include "All.h"
//#define VERBOSE

#include "Window.h"

// -- Callbacks

namespace Engine {
	Window::Window() : Object("Window")
	{
		instance = this;

		state = State::RUNNING;

		width = 100;
		height = 100;

		int count, windowWidth, windowHeight, monitorX, monitorY;

		// Assuming that main monitor is in the 0 position
		GLFWmonitor** monitors = glfwGetMonitors(&count);
		const GLFWvidmode* videoMode = glfwGetVideoMode(monitors[0]);

		// Width: 75% of the screen
		windowWidth = static_cast<int>(videoMode->width / 1.5);
		windowHeight = static_cast<int>(videoMode->height / 16 * 9); // Aspect ratio 16 to 9
		glfwGetMonitorPos(monitors[0], &monitorX, &monitorY);

		// Initialize window
		window = glfwCreateWindow(scene->settings.screenWidth, scene->settings.screenHeight, scene->settings.name.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(window); // Make the window's context current

		glfwSetWindowAttrib(window, GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		glfwSetWindowPos(window, monitorX + (videoMode->width - windowWidth) / 2, monitorY + (videoMode->height - windowHeight) / 2);

		// show the window
		glfwShowWindow(window);

		// Hide the border of the window
		glfwSetWindowAttrib(window, GLFW_DECORATED, GLFW_FALSE);
		

		// Specifies whether the windowed mode window will be resizable by the user.
		glfwSetWindowAttrib(window, GLFW_RESIZABLE, false);

		//glfwSetWindowAttrib(window, GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);

		// set the visibility window hint to false for subsequent window creation
		//glfwSetWindowAttrib(window, GLFW_VISIBLE, GLFW_FALSE);
		
		
		
		
		
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

	void Window::Render()
	{
		scene->Render();
		glfwSwapBuffers(window);

		// Check the Game state to see whether to close
		if (scene->state == Scene::State::CLOSING) glfwSetWindowShouldClose(window, true);
	}

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