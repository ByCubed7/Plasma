// By @ByCubed7 on Twitter

//#include "All.h"
//#define VERBOSE

#include "Core.h"
#include "Components.h"
#include "Tilemaps.h"
#include "Render.h"
#include "Audio.h"
#include "UI.h"

#include "PlayerCollisionEventManager.h"
#include "WarpComponent.h"
#include "TileLockedController.h"
#include "Muncher.h"
#include "ScoreTracker.h"
#include "InputDirector.h"
#include "PlayerInputDirector.h"
#include "GuardGhostInputDirector.h"
#include "AmbushGhostInputDirector.h"
#include "GhostStateComponent.h"

#include <GLFW/glfw3.h>

#include <iostream>

#include <windows.h>
#include <tchar.h>


int main(int argc, char* argv[])
{
	Engine::App app = Engine::App();

	Settings config;
	config.PPU = 20;
	config.screenHeight = config.PPU * (31 + 1);
	config.screenWidth  = config.PPU * 28;

	Engine::Scene* scene = app.CreateGame(config);
	//Scene scene = pacman.scene; // Get the default scene

	// Prepares an OpenGL context so that we can send API calls
	app.Build(scene);

	scene->Initialize();

	// - Load textures
	Resources::LoadTexture("assets/textures/Player.png", true, "player");
	Resources::LoadTexture("assets/textures/Ghost.png", true, "ghost");
	Resources::LoadTexture("assets/textures/Pip.png", true, "pip");
	Resources::LoadTexture("assets/textures/Cherry.png", true, "cherry");
	Resources::LoadTexture("assets/textures/Tilesheet.png", true, "tilesheet");

	// Load levels
	Resources::LoadTilemap("assets/tilemaps/Pacman.tmx", "tilesheet");

	Resources::LoadWav("assets/audio/Venus by SketchyLogic.wav", "venus");
	
	Resources::LoadWav("assets/audio/beginning.wav", "beginning");
	//Resources::LoadWav("assets/audio/chomp.wav", "chomp");
	//Resources::LoadWav("assets/audio/death.wav", "death");
	//Resources::LoadWav("assets/audio/eatfruit.wav", "eatfruit");
	//Resources::LoadWav("assets/audio/eatghost.wav", "eatghost");
	//Resources::LoadWav("assets/audio/extrapac.wav", "extrapac");
	//Resources::LoadWav("assets/audio/intermission.wav", "intermission");


	// - Create audio
	//GameObject* audi = scene->CreateGameObject();

	//AudioSourceComponent* audiComp = new AudioSourceComponent(audi);
	//audiComp->Attach(Resources::GetWav("beginning"));

	//audiComp->source->Play();
	//while (source->IsPlaying()) ;
	//cout << "No longer playing" << endl;

	// - - - Add Tilemap - - - 
	GameObject* tilemap = scene->CreateGameObject();
	tilemap->position = Vector2(config.PPU/2, config.PPU/2);

	TilemapComponent* tilemapTilemap = new TilemapComponent(tilemap);

	tilemapTilemap
		->SetTilemap(Resources::GetTilemap("tilesheet"))
		->Set(Resources::GetTexture("tilesheet"))
		->Bind(scene->renderer);






	// Mainloop
	return app.Run(scene);
}