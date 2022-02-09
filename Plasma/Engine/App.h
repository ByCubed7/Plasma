// By @ByCubed7 on Twitter

#pragma once

#include "../Library/glad.h"
#include <GLFW/glfw3.h>

#include "Audio/AudioScene.h"

#include "Scene.h"
#include "Settings.h"
#include "Resources.h"

#include <iostream>


class Scene;
namespace Engine { class Scene; }


class App
{
public:

	static App* instance;

	App();

	Engine::Scene* CreateGame(Settings& gameConfig);
	//Scene* GetScene();

	/// <summary>
	/// Prepares and configuares the GLWF API to recieve calls, creates the window, prepares window callbacks. ect
	/// </summary>
	/// <param name="scene">- The scene to prepare GLWF with.</param>
	/// <returns>The result ID of the opperation, if any.</returns>
	int Prepare(Engine::Scene* scene);

	/// <summary>
	/// Runs the Mainloop.
	/// </summary>
	/// <param name="scene"></param>
	/// <returns>The result ID of the opperation, if any.</returns>
	int Run(Engine::Scene* scene);


private:
	GLFWwindow* window;
	Engine::Scene* scene;

	/// <summary>
	/// Notifys when a physical key is pressed, released or repeats.
	/// </summary>
	/// <param name="window">- the window that the event was sent to</param>
	/// <param name="key">- the key token associated with the key that was pressed. See: https://www.glfw.org/docs/3.3/group__keys.html </param>
	/// <param name="scancode">- scancode is unique for every key, regardless of whether it has a key token</param>
	/// <param name="action">- descirbes the type of callback that has occured. Is one of GLFW_PRESS, GLFW_REPEAT or GLFW_RELEASE</param>
	/// <param name="mode">The modifier key flags. See: https://www.glfw.org/docs/3.3/group__mods.html </param>
	void GraphicsCallbackKey(GLFWwindow* window, int key, int scancode, int action, int mode);

	void GraphicsCallbackMouseButton(GLFWwindow* window, int button, int action, int mods);

	void GraphicsCallbackCursorPosition(GLFWwindow* window, double xpos, double ypos);

	void GraphicsCallbackFramebuffer(GLFWwindow* window, int width, int height);

	void GraphicsCallbackException(GLenum source, GLenum type, unsigned int id, GLenum severity, GLsizei length, const char* message, const void* userParam);
};

