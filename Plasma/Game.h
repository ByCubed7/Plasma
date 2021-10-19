#pragma once

#include "Library/glad.h"
#include "Settings.h"
#include "Input.h"
#include <list>
#include "GameObject.h"
//#include <GLFW/glfw3.h>

/*/ Represents the current state of the game
enum GameState {
	GAME_ACTIVE,
	GAME_MENU,
	GAME_WIN
};
//*/

// Forward declaration
class GameObject;

// Game holds all game-related state and functionality.
// Combines all game-related data into a single class for
// easy access to each of the components and manageability.
class Game
{
public:
	enum class State { ACTIVE, MENU, CLOSING };

	float timeStep = 1.0f;

	// The game state
	State state;

	Input input;
	
	unsigned int width, height;

	std::vector<std::unique_ptr<GameObject>> gameObjects = {};

	// Constructor
	Game(const Settings& setting);
	
	// Destructor
	~Game();

	void AddGameObject(GameObject * gameObject);

	// Initialize game state 
	// load all shaders, textures and levels
	void Init();

	// Game loop

	void ProcessInput(double delta);
	void Update(double delta);
	void Render();
};