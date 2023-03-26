// By @ByCubed7 on Twitter

#pragma once

#include "Audio/AudioScene.h"

#include "Scene.h"

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

		/// <summary>Prepares and configuares GLWF to recieve calls, creates the window, prepares window callbacks. ect</summary>
		/// <returns>The result ID of the opperation, if any.</returns>
		int build();

		/// <summary>Loads a scene onto the app</summary>
		/// <param name="newScene">- the scene to load.</param>
		void load(Engine::Scene* newScene);

		/// <summary>Runs the Mainloop.</summary>
		/// <param name="scene"></param>
		/// <returns>The result ID of the opperation, if any.</returns>
		int run();

		// Returns the current window
		Engine::Window* getWindow();

		// Returns the current loaded scene
		Engine::Scene* getScene();
		
		// Returns the size of the window
		Vector2Int getSize();

		// Sets the size of the window
		void setSize(Vector2Int newSize);

	private:
		Engine::Window* window;
		Engine::Scene* scene;

		Vector2Int size;

		void GraphicsCallbackException(GLenum source, GLenum type, unsigned int id, GLenum severity, GLsizei length, const char* message, const void* userParam);
	};

}