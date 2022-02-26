// By @ByCubed7 on Twitter

#include "All.h"
//#define VERBOSE

#include "Window.h"

#include <windows.h>
#include <tchar.h>

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
		glfwWindowHint(GLFW_FOCUSED, GLFW_FALSE);
		glfwWindowHint(GLFW_FLOATING, GLFW_TRUE);
		glfwWindowHint(GLFW_FOCUS_ON_SHOW, GLFW_FALSE);

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

		//
		/*if (msg == WM_WINDOWPOSCHANGING) { 
			if ((WNDPOS*)lparam)->hwndInsertAfter != lastWindowPos) 
				SetWindowPos(otherWindowHwnd, hwnd, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE) 
		}*/
	
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
		//else if (action == GLFW_RELEASE) App.input.Releas.ed(key);

		/*

		// Send to window behind
		HWND notepad = FindWindow(_T(title), NULL);
		HWND edit = FindWindowEx(notepad, NULL, _T("Edit"), NULL);
		SendMessage(edit, WM_SETTEXT, NULL, (LPARAM) _T("hello"));

		SetForegroundWindow(notepad);

		*/
	}

	void Window::GraphicsCallbackMouseButton(GLFWwindow* window, int button, int action, int mods)
	{
		if (action != GLFW_PRESS && action != GLFW_RELEASE) return;

		//if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
		scene->input.SetMouseButton(button, action == GLFW_PRESS);

		/*/ CLICK
		POINT pos_cursor;
		GetCursorPos(&pos_cursor);


		INPUT inputs[3] = { 0 };

		inputs[0].type = INPUT_MOUSE;
		inputs[0].mi.dx = pos_cursor.x; // desired X coordinate
		inputs[0].mi.dy = pos_cursor.y; // desired Y coordinate
		inputs[0].mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE;

		inputs[1].type = INPUT_MOUSE;
		inputs[1].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;

		inputs[2].type = INPUT_MOUSE;
		inputs[2].mi.dwFlags = MOUSEEVENTF_LEFTUP;

		SendInput(3, inputs, sizeof(INPUT));
		//*/
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