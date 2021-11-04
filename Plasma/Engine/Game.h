#pragma once

#include "../Library/glad.h"

#include "Settings.h"
#include "Input.h"
#include "SpriteRenderer.h"
#include "TextRenderer.h"
#include "Renderer.h"

#include <list>

// Forward declaration
class GameObject;

// Game holds all game-related state and functionality.
// Combines all game-related data into a single class for
// easy access to each of the components and manageability.
class Game
{
public:
	enum class State { ACTIVE, PAUSED, CLOSING };

	float timeStep = 1.0f;

	// The game state
	State state;

	Input input;
	
	unsigned int width, height;

	//SpriteRenderer* spriteRenderer;
	//TextRenderer* text;
	Renderer* renderer;

	std::vector<std::unique_ptr<GameObject>> gameObjects = {};

	// Constructor
	Game(const Settings& setting);
	
	// Destructor
	~Game();

	void AddGameObject(GameObject * gameObject);

	// Initialize game state 
	// load all shaders, textures and levels
	virtual void Init();

	// Game loop

	void ProcessInput(double delta);

	void GInit();
	void GUpdate(double delta);
	void GRender();

	virtual void Update(double delta);
	virtual void Render();

};