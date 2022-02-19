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
namespace Engine { class Scene; class Window; }

namespace Engine {
	class App
	{
	public:

		static App* instance;

		App();

		Engine::Scene* CreateGame(Settings& gameConfig);
		//Scene* GetScene();

		/// <summary>
		/// Prepares and configuares GLWF to recieve calls, creates the window, prepares window callbacks. ect
		/// </summary>
		/// <param name="scene">- The scene to prepare with.</param>
		/// <returns>The result ID of the opperation, if any.</returns>
		int Build(Engine::Scene* scene);

		/// <summary>
		/// Runs the Mainloop.
		/// </summary>
		/// <param name="scene"></param>
		/// <returns>The result ID of the opperation, if any.</returns>
		int Run(Engine::Scene* scene);


	private:
		Engine::Window* window;
		Engine::Scene* scene;

		void GraphicsCallbackException(GLenum source, GLenum type, unsigned int id, GLenum severity, GLsizei length, const char* message, const void* userParam);
	};

}