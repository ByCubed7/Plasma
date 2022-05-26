// By @ByCubed7 on Twitter

#pragma once

#include "Object.h"
#include "Vector.h"
#include "Scene.h"

#include <GLFW/glfw3.h>
//#include <glm/glm.hpp>

#include <windows.h>

// Forward declaration


namespace Engine 
{
	// Forward declaration
	class Component;
	class Scene;
	class App;

	class Window : public Object
	{
	public:
		enum class State { RUNNING, QUITTING };
		State state;
		
		static Window* instance;

		// Constructors
		Window(App* app);

		void LoadScene(Scene* newScene);
		void Update();
		GLFWwindow* Get();
		void Render();
		void Title(std::string newName);

		int GetPPU();
		Vector2Int GetMonitorSize();

		void UpdateSize();

	private:
		App* app;

		int PPU;

		GLFWwindow* window;
		Engine::Scene* scene;

		std::string title;
		Vector2Int position;

		GLFWmonitor* monitor;
		Vector2Int monitorSize;
		Vector2Int monitorPosition;

		/// <summary>
		/// Notifys when a physical key is pressed, released or repeats.
		/// </summary>
		/// <param name="window">- the window that the event was sent to</param>
		/// <param name="key">- the key token associated with the key that was pressed. See: https://www.glfw.org/docs/3.3/group__keys.html </param>
		/// <param name="scancode">- scancode is unique for every key, regardless of whether it has a key token</param>
		/// <param name="action">- descirbes the type of callback that has occured. Is one of GLFW_PRESS, GLFW_REPEAT or GLFW_RELEASE</param>
		/// <param name="mode">- The modifier key flags. See: https://www.glfw.org/docs/3.3/group__mods.html </param>
		void GraphicsCallbackKey(GLFWwindow* window, int key, int scancode, int action, int mode);
		void GraphicsCallbackMouseButton(GLFWwindow* window, int button, int action, int mods);
		void GraphicsCallbackCursorPosition(GLFWwindow* window, double xpos, double ypos);
		void GraphicsCallbackFramebuffer(GLFWwindow* window, int width, int height);

		HWND hWnd;
	};

}