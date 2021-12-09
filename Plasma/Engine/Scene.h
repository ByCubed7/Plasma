// By @ByCubed7 on Twitter

#pragma once

#include "../Library/glad.h"

#include "Input.h"
#include "Settings.h"
#include "Renderers.h"

#include <list>

#include "Audio/AudioScene.h"

using namespace std;

// Forward declaration
class GameObject;
class Component;
class BoxColliderComponent;

namespace Engine {
	/// <summary>
	/// Game holds all game-related state and functionality.
	/// Combines all game-related data into a single class for easy access to 
	/// each of the components and manageability.
	/// </summary>
	class Scene
	{
	public:
		enum class State { ACTIVE, PAUSED, CLOSING };

		float timeStep = 1.0f;

		// The game state
		State state;

		Input input;
		GameConfig settings;

	
		unsigned int width, height;

		Audio::Scene* audio;
		Render::Renderers* renderer;

		list<GameObject*> gameObjects;
		list<Component*> components;

		// Collision
		list<BoxColliderComponent*> colliders;
		map<BoxColliderComponent*, BoxColliderComponent*> collidersColliding;


		// Constructor
		Scene(GameConfig& setting);
	
		// Destructor
		~Scene();

		GameObject* CreateGameObject();
		void AddGameObject(GameObject* gameObject);
		void AddComponent(Component* component);
		//void AddComponent(GameObject* gameObject, Component* component);

		/// <summary>
		/// Stores the state of the current input. Keyboard presses, mouse position, ect
		/// </summary>
		/// <param name="delta">- the interval in seconds from the last frame to the current one.</param>
		void ProcessInput(double delta);

		/// <summary>
		/// Initializes the DEFAULT shaders, textures, projection, renderers and fonts.
		/// </summary>
		void Initialize();

		/// <summary>
		/// Called every frame. Updates all components, collisions and events.
		/// </summary>
		/// <param name="delta">- the interval in seconds from the last frame to the current one.</param>
		void Update(double delta);

		/// <summary>
		/// Called at the end of each frame. Renders all of the components.
		/// </summary>
		void Render();
	};
}