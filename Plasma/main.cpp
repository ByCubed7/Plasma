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
		->SetColour(Colour(180, 0, 255))
		->AnimationSpeed(8);

	Muncher* playerMuncher = new Muncher(player);
	playerMuncher->SetTilemap(tilemapTilemap);

	WarpComponent* playerWarp = new WarpComponent(player);
	playerWarp->SetOffset(player->scale * config.PPU);

	TileLockedController* playerController = new TileLockedController(player);
	playerController
		->SetSpeed((float) 5 * config.PPU)
		->SetTilemap(tilemapTilemap)
		->SetRotatable(true);

	PlayerInputDirector* playerInput = new PlayerInputDirector(player);
	playerInput->SetController(playerController);

	BoxColliderComponent* playerCollider = new BoxColliderComponent(player);
	playerCollider
		->SetSize(Vector2(20))
		->Bind(scene);

	PlayerCollisionEventManager* playerColliderEventMng = new PlayerCollisionEventManager(player);
	playerColliderEventMng->Subscribe(playerCollider);


	// - - - Add Ghosts - - - 

	// BLINKY 
	GameObject* guardGhost = scene->CreateGameObject();
	guardGhost->position = Vector2(config.HalfWidth(), config.HalfHeight());
	guardGhost->scale = 2;

	SpriteComponent* guardGhostSprite = new SpriteComponent(guardGhost);
	guardGhostSprite
		->Set(Resources::GetTexture("ghost"))
		->SetColour({ 255, 0, 0 })
		->AnimationSpeed(4);

	TileLockedController* guardGhostController = new TileLockedController(guardGhost);
	guardGhostController
		->SetTilemap(tilemapTilemap)
		->SetSpeed(75);

	GhostStateComponent* guardGhostState = new GhostStateComponent(guardGhost);
	guardGhostState->Chase();

	GuardGhostInputDirector* guardGhostAI = new GuardGhostInputDirector(guardGhost);
	guardGhostAI
		->SetTarget(player)
		->SetStateComponent(guardGhostState)
		->SetController(guardGhostController);
	
	WarpComponent* guardGhostWarp = new WarpComponent(guardGhost);
	guardGhostWarp->SetOffset(guardGhost->scale * config.PPU * 0.5f);

	BoxColliderComponent* guardGhostCollider = new BoxColliderComponent(guardGhost);
	guardGhostCollider
		->SetSize(Vector2(20))
		->Bind(scene);


	// PINKY
	GameObject* ambushGhost = scene->CreateGameObject();
	ambushGhost->position = Vector2(config.HalfWidth(), config.HalfHeight());
	ambushGhost->scale = 2;

	SpriteComponent* ambushGhostSprite = new SpriteComponent(ambushGhost);
	ambushGhostSprite
		->Set(Resources::GetTexture("ghost"))
		->SetColour(Colour(255, 128, 255))
		->AnimationSpeed(4);

	TileLockedController* ambushGhostController = new TileLockedController(ambushGhost);
	ambushGhostController
		->SetTilemap(tilemapTilemap)
		->SetSpeed(70);

	GhostStateComponent* ambushGhostState = new GhostStateComponent(ambushGhost);
	ambushGhostState->Chase();

	AmbushGhostInputDirector* ambushGhostAI = new AmbushGhostInputDirector(ambushGhost);
	ambushGhostAI
		->SetTarget(player)
		->SetStateComponent(ambushGhostState)
		->SetController(ambushGhostController);

	WarpComponent* ambushGhostWarp = new WarpComponent(ambushGhost);
	ambushGhostWarp->SetOffset(ambushGhost->scale* config.PPU * 0.5f);

	BoxColliderComponent* ambushGhostCollider = new BoxColliderComponent(ambushGhost);
	ambushGhostCollider
		->Bind(scene)
		->SetSize(Vector2(20));


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