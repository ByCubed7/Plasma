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
#include "TileLockedCharacterController.h"
#include "Muncher.h"

#include <iostream>
#include "ScoreTracker.h"

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

	audiComp->source->Play();


	//while (source->IsPlaying()) ;
	//cout << "No longer playing" << endl;

	// - Create Tilemap

	//* Create the tilemap
	GameObject* tilemap = scene->CreateGameObject();
	tilemap->position = Vector2(config.PPU/2, config.PPU/2);

	TilemapComponent* tilemapTilemap = new TilemapComponent(tilemap);

	tilemapTilemap
		->SetTilemap(Resources::GetTilemap("tilesheet"))
		->Set(Resources::GetTexture("tilesheet"))
		->Bind(scene->renderer);



	// - Create player
	GameObject* player = scene->CreateGameObject();
	player->position = config.PPU * 0.5f;
	player->scale = { 2,2 };

	SpriteComponent* playerSprite = new SpriteComponent(player);

	playerSprite
		->Set(Resources::GetTexture("player"))
		->AnimationSpeed(8);

	Muncher* playerMuncher = new Muncher(player);
	playerMuncher->SetTilemap(tilemapTilemap);

	//CharacterControllerComponent* playerController = new CharacterControllerComponent();
	//player->AddComponent(playerController);

	TileLockedCharacterController* playerController = new TileLockedCharacterController(player);
	playerController->SetSpeed(5 * config.PPU);
	playerController->SetTilemap(tilemapTilemap);

	WarpComponent* playerWarp = new WarpComponent(player);
	playerWarp->SetOffset(player->scale * config.PPU);

	BoxColliderComponent* playerCollider = new BoxColliderComponent(player);
	playerCollider->Bind(scene);

	PlayerCollisionEventManager* playerColliderEventMng = new PlayerCollisionEventManager(player);
	playerColliderEventMng->Bind(playerCollider);





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