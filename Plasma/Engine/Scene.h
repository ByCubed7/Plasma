// By @ByCubed7 on Twitter

#pragma once

#include "Input.h"

#include <list>
#include <map>

// Forward declaration
class BoxColliderComponent;

namespace Audio { class Scene; }
namespace Render { struct Renderers; }


namespace Engine 
{
	// Forward declaration
	class App;
	class Window;
	class GameObject;
	class Component;

	/// <summary>
	/// Game holds all game-related state and functionality.
	/// Combines all game-related data into a single class for easy access to 
	/// each of the components and manageability.
	/// </summary>
	class Scene
	{
	public:
		enum class State { ACTIVE, PAUSED, CLOSING };

		App* app;

		float timeStep = 1.0f;

		// The game state
		State state;

		Audio::Scene* audio;
		Render::Renderers* renderer;

		std::list<GameObject*> gameObjects;
		std::list<Component*> components;

		// Collision
		std::list<BoxColliderComponent*> colliders;
		std::map<BoxColliderComponent*, BoxColliderComponent*> collidersColliding;

		Window* getWindow();

		// Constructor
		Scene(App* app);
	
		// Destructor
		~Scene();

		GameObject* CreateGameObject();
		void AddGameObject(GameObject* gameObject);
		void addComponent(Component* component);
		//void addComponent(GameObject* gameObject, Component* component);

		/// <summary>
		/// Stores the state of the current input. Keyboard presses, mouse position, ect
		/// </summary>
		void ProcessInput();

		/// <summary>
		/// Initializes the DEFAULT shaders, textures, projection, renderers and fonts.
		/// </summary>
		void load();

		void UpdateProjection();

		/// <summary>
		/// Called every frame. Updates all components, collisions and events.
		/// </summary>
		/// <param name="delta">- the interval in seconds from the last frame to the current one.</param>
		void update(double time, double delta);

		/// <summary>
		/// Called at the end of each frame. Renders all of the components.
		/// </summary>
		void Render();
	};
}