// By @ByCubed7 on Twitter

#include "All.h"
//#define VERBOSE

#include "Window.h"

#include "App.h"

#include <GLFW/glfw3.h>
//#include <glm/glm.hpp>

#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

#include <windows.h>
#include <tchar.h>

namespace Engine {
	Window* Window::instance = nullptr;

	Window::Window(App* app) : Object("Window")
	{
		instance = this;
		this->app = app;

		title = "Title";

		state = State::RUNNING;

		x = 0;
		y = 0;

		PPU = 20;


		// See: https://gist.github.com/esmitt/e722265936f0ebe96fc166bdf1fff41b

		glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
		
		// Set the visibility window hint to false for subsequent window creation
		glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

		// Specifies whether the window will be given input focus when glfwShowWindow is called
		glfwWindowHint(GLFW_FOCUS_ON_SHOW, GLFW_FALSE);
		
		// By default, newly created windows are given input focus. But we don't want this.
		glfwWindowHint(GLFW_FOCUSED, GLFW_FALSE);

		// Specifies whether the windowed mode window will be floating above other regular windows, also called topmost or always-on-top.
		// Stops from hiding behind windows when not focused
		glfwWindowHint(GLFW_FLOATING, GLFW_TRUE);



		// Initialize window
		Vector2 size = app->GetSize();
		window = glfwCreateWindow((int)size.x, (int)size.y, title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(window); // Make the window's context 
		glfwSetWindowAspectRatio(window, 1, 1);
		glfwShowWindow(window);


		// - - MONITOR
		monitor = glfwGetPrimaryMonitor();
		glfwGetMonitorWorkarea(monitor, &monitorX, &monitorY, &monitorWidth, &monitorHeight);

		//glfwMaximizeWindow(window);

		glfwSetWindowPos(window, 0, 0);
		glfwShowWindow(window);
		//*/

		// Hide the border of the window
		glfwSetWindowAttrib(window, GLFW_DECORATED, GLFW_FALSE);



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


		// Grab the HWND of the window
		// Defining GLFW_EXPOSE_NATIVE_WIN32 to grab the glfw3native macro
		hWnd = glfwGetWin32Window(window);

		// Grab window ex+style
		long style = GetWindowLong(hWnd, GWL_STYLE);
		long exstyle = GetWindowLong(hWnd, GWL_EXSTYLE);

		// - - IGNORE FOCUS
		// This took months to work out--
		// This tells the window to ignore all focus calls, causing them to fallback behind the window
		// https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getwindowlonga
		// https://docs.microsoft.com/en-us/windows/win32/winmsg/extended-window-
		// 32	  (0x20)    is WS_EX_TRANSPARENT
		// 524288 (0x80000) is WS_EX_LAYERED
		exstyle |= WS_EX_LAYERED | WS_EX_TRANSPARENT;
		//*/


		// - - HIDE FROM TASKBAR
		// https://stackoverflow.com/questions/7219063/win32-how-to-hide-3rd-party-windows-in-taskbar-by-hwnd
		exstyle &= ~(WS_VISIBLE);    // this works - window become invisible 
		exstyle |= WS_EX_TOOLWINDOW;   // flags don't work - windows remains in taskbar
		exstyle &= ~(WS_EX_APPWINDOW);
		//*/

		// Update Style
		ShowWindow(hWnd, SW_HIDE); // hide the window
		SetWindowLong(hWnd, GWL_STYLE, style);
		SetWindowLong(hWnd, GWL_EXSTYLE, exstyle);
		ShowWindow(hWnd, SW_SHOW); // show the window for the new style to come into effect
		//*/


		// Done setting up the window, reset the window hints.
		//glfwDefaultWindowHints();

		gladLoadGL();

		//UpdateSize();
		std::cout << "[Window::Ctor] END " << std::endl;
	}

	void Window::LoadScene(Scene* newScene)
	{
		scene = newScene;
	}

	void Window::Render()
	{
		scene->Render();
		glfwSwapBuffers(window);

		// Get mouse position
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		//std::cout << xpos << ":" << ypos << std::endl;
		scene->input.SetMousePosition(xpos, ypos);
		//scene->input.SetMousePosition(20, 20);

		// Check the Game state to see whether to close
		if (scene->state == Scene::State::CLOSING) {
			state = State::QUITTING;
			glfwSetWindowShouldClose(window, true);
		}

		GLenum err;
		while ((err = glGetError()) != GL_NO_ERROR)
			std::cout << "[Window::Render] OpenGL Error: " << err << std::endl;
	}

	void Window::Title(std::string newName)
	{
		title = newName;
		glfwSetWindowTitle(window, title.c_str());
	}

	void Window::UpdateSize()
	{
		Vector2 size = app->GetSize();
		glfwSetWindowSize(window, (int)size.x, (int)size.y);
	}

	int Window::GetPPU()
	{
		return PPU;
	}

	Vector2 Window::GetMonitorSize()
	{
		return Vector2(monitorWidth, monitorHeight);
	}

	//

	void Window::GraphicsCallbackKey(GLFWwindow* window, int key, int scancode, int action, int mode)
	{
		if (!scene->input.KeyExists(key)) return;
		if (action != GLFW_PRESS && action != GLFW_RELEASE) return;

		scene->input.SetKey(key, action == GLFW_PRESS);
		//if (action == GLFW_PRESS) App.input.Pressed(key);
		//else if (action == GLFW_RELEASE) App.input.Releas.ed(key);

		/* WE SHOULDNT HAVE TO DO THIS

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
	}

	void Window::GraphicsCallbackCursorPosition(GLFWwindow* window, double xpos, double ypos)
	{
		//scene->input.SetMousePosition(xpos, ypos);
	}

	void Window::GraphicsCallbackFramebuffer(GLFWwindow* window, int width, int height)
	{
		//glViewport(0, 0, width, height);
	}
}