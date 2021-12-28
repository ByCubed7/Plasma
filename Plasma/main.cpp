// By @ByCubed7 on Twitter

#include "Library/glad.h"
#include <GLFW/glfw3.h>

#include "Engine/App.h"
#include "Engine/Scene.h"
#include "Engine/Resources.h"
#include "Engine/Settings.h"
#include "Engine/Gameobject.h"
#include "Engine/SpriteComponent.h"
#include "Engine/TilemapComponent.h"
#include "Engine/CharacterControllerComponent.h"
#include "Engine/AudioSourceComponent.h"

#include "Engine/UI/TextboxComponent.h"

#include "PlayerCollisionEventManager.h"
#include "WarpComponent.h"
#include "TileLockedController.h"
#include "Muncher.h"
#include "ScoreTracker.h"

#include "InputDirector.h"
#include "PlayerInputDirector.h"
#include "GuardGhostInputDirector.h"
#include "AmbushGhostInputDirector.h"

#include <iostream>

int main(int argc, char* argv[])
{
	App app = App();

	Settings config;
	config.PPU = 20;
	config.screenHeight = config.PPU * (31 + 1);
	config.screenWidth  = config.PPU * 28;

	Engine::Scene* scene = app.CreateGame(config);
	//Scene scene = pacman.scene; // Get the default scene

	// Prepares an OpenGL context so that we can send API calls
	app.Prepare(scene);

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
	GameObject* audi = scene->CreateGameObject();

	AudioSourceComponent* audiComp = new AudioSourceComponent(audi);
	audiComp->Attach(Resources::GetWav("beginning"));

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



	// - - - Add Player - - - 
	GameObject* player = scene->CreateGameObject();
	player->position = config.PPU * 0.5f;
	player->scale = 2;

	SpriteComponent* playerSprite = new SpriteComponent(player);

	playerSprite
		->Set(Resources::GetTexture("player"))
		->SetColour({ 0.7f, 0.7f, 0.3f })
		->AnimationSpeed(8);

	Muncher* playerMuncher = new Muncher(player);
	playerMuncher->SetTilemap(tilemapTilemap);

	WarpComponent* playerWarp = new WarpComponent(player);
	playerWarp->SetOffset(player->scale * config.PPU);

	TileLockedController* playerController = new TileLockedController(player);
	playerController
		->SetSpeed(5 * config.PPU)
		->SetTilemap(tilemapTilemap)
		->SetRotatable(true);

	PlayerInputDirector* playerInput = new PlayerInputDirector(player);
	playerInput->SetController(playerController);

	BoxColliderComponent* playerCollider = new BoxColliderComponent(player);
	playerCollider->Bind(scene);

	PlayerCollisionEventManager* playerColliderEventMng = new PlayerCollisionEventManager(player);
	playerColliderEventMng->Bind(playerCollider);


	// - - - Add Ghosts - - - 

	// BLINKY 
	GameObject* guardGhost = scene->CreateGameObject();
	guardGhost->position = Vector2(config.HalfWidth(), config.HalfHeight());
	guardGhost->scale = 2;

	SpriteComponent* guardGhostSprite = new SpriteComponent(guardGhost);
	guardGhostSprite
		->Set(Resources::GetTexture("ghost"))
		->SetColour({ 1, 0, 0 })
		->AnimationSpeed(4);

	TileLockedController* guardGhostController = new TileLockedController(guardGhost);
	guardGhostController
		->SetTilemap(tilemapTilemap)
		->SetSpeed(75);

	GuardGhostInputDirector* guardGhostAI = new GuardGhostInputDirector(guardGhost);
	guardGhostAI
		->SetTarget(player)
		->SetController(guardGhostController);
	
	WarpComponent* guardGhostWarp = new WarpComponent(guardGhost);
	guardGhostWarp->SetOffset(guardGhost->scale * config.PPU * 0.5f);

	BoxColliderComponent* guardGhostCollider = new BoxColliderComponent(guardGhost);
	guardGhostCollider->Bind(scene);


	// PINKY
	GameObject* ambushGhost = scene->CreateGameObject();
	ambushGhost->position = Vector2(config.HalfWidth(), config.HalfHeight());
	ambushGhost->scale = 2;

	SpriteComponent* ambushGhostSprite = new SpriteComponent(ambushGhost);
	ambushGhostSprite
		->Set(Resources::GetTexture("ghost"))
		->SetColour({ 1, 0.5f, 1 })
		->AnimationSpeed(4);

	TileLockedController* ambushGhostController = new TileLockedController(ambushGhost);
	ambushGhostController
		->SetTilemap(tilemapTilemap)
		->SetSpeed(70);

	AmbushGhostInputDirector* ambushGhostAI = new AmbushGhostInputDirector(ambushGhost);
	ambushGhostAI
		->SetTarget(player)
		->SetController(ambushGhostController);

	WarpComponent* ambushGhostWarp = new WarpComponent(ambushGhost);
	ambushGhostWarp->SetOffset(ambushGhost->scale* config.PPU * 0.5f);

	BoxColliderComponent* ambushGhostCollider = new BoxColliderComponent(ambushGhost);
	ambushGhostCollider->Bind(scene);


	// - - - Add UI - - - 
	GameObject* scoreGameObject = scene->CreateGameObject();
	scoreGameObject->position = Vector2(0, config.screenHeight - config.PPU);
	scoreGameObject->scale = { 1,1 };

	UI::TextboxComponent* scoreTextbox = new UI::TextboxComponent(scoreGameObject);
	//scoreTextbox->text = "SCORE: XXXXX";

	ScoreTracker* scoreTracker = new ScoreTracker(scoreGameObject);
	scoreTracker->SetTextbox(scoreTextbox);
	
	playerMuncher->SetScore(scoreTracker);

	return app.Run(scene);
}