// By @ByCubed7 on Twitter

#pragma once

#include "../Library/glad.h"
#include <GLFW/glfw3.h>

#include "Audio/AudioScene.h"

#include "Scene.h"
#include "Resources.h"

#include <iostream>


class Scene;
namespace Engine { class Scene; class Window; }

namespace Engine 
{
	class App
	{
	public:
		static App* instance;

		App();

		Engine::Scene* CreateGame();
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

		Engine::Window* GetWindow();
		Engine::Scene* GetScene();
		
		Vector2 GetSize();
		void SetSize(Vector2 newSize);

	private:
		Engine::Window* window;
		Engine::Scene* scene;

		Vector2 size;

		void GraphicsCallbackException(GLenum source, GLenum type, unsigned int id, GLenum severity, GLsizei length, const char* message, const void* userParam);
	};

}