// By @ByCubed7 on Twitter

#pragma once

#include "Audio/AudioScene.h"

#include "Scene.h"
#include "Resources.h"

#include "OpenGL.h"

#include <iostream>


namespace Engine 
{
	class Scene; 
	class Window;

	class App
	{
	public:
		static App* instance;
		Input input;

		App();

		Engine::Scene* CreateGame();
		//Scene* GetScene();

		/// <summary>
		/// Prepares and configuares GLWF to recieve calls, creates the window, prepares window callbacks. ect
		/// </summary>
		/// <returns>The result ID of the opperation, if any.</returns>
		int Build();

		/// <summary>
		/// Loads a scene onto the app
		/// </summary>
		/// <param name="newScene">- the scene to load.</param>
		void Load(Engine::Scene* newScene);

		/// <summary>
		/// Runs the Mainloop.
		/// </summary>
		/// <param name="scene"></param>
		/// <returns>The result ID of the opperation, if any.</returns>
		int Run();

		// Returns the current window
		Engine::Window* GetWindow();

		// Returns the current loaded scene
		Engine::Scene* GetScene();
		
		// Returns the size of the window
		Vector2Int GetSize();

		// Sets the size of the window
		void SetSize(Vector2Int newSize);

	private:
		Engine::Window* window;
		Engine::Scene* scene;

		Vector2Int size;

		void GraphicsCallbackException(GLenum source, GLenum type, unsigned int id, GLenum severity, GLsizei length, const char* message, const void* userParam);
	};

}