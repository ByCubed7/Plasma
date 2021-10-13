#include "glad.h"
#include "Settings.h"
//#include <GLFW/glfw3.h>

// Represents the current state of the game
enum GameState {
	GAME_ACTIVE,
	GAME_MENU,
	GAME_WIN
};

// Game holds all game-related state and functionality.
// Combines all game-related data into a single class for
// easy access to each of the components and manageability.
class Game
{
public:
	//enum State { GAME_ACTIVE, GAME_MENU, GAME_WIN };

	// Game state
	GameState State;
	bool Keys[1024];
	unsigned int Width, Height;
	
	// Constructor
	Game(const Settings& setting);
	
	// Destructor
	~Game();

	// Initialize game state 
	// load all shaders, textures and levels
	void Init();

	// Game loop

	void ProcessInput(float dt);
	void Update(float dt);
	void Render();
};