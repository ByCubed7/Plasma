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

#include "PlayerCollisionEventManager.h"
#include "WarpComponent.h"
#include "TileLockedCharacterController.h"

#include <iostream>

int main(int argc, char* argv[])
{
	App app = App();

	GameConfig gameConfig;
	gameConfig.PPU = 32;
	gameConfig.screenHeight = gameConfig.PPU * 31;
	gameConfig.screenWidth  = gameConfig.PPU * 28;

	Engine::Scene* scene = app.CreateGame(gameConfig);
	//Scene scene = pacman.scene; // Get the default scene

	// Prepares an OpenGL context so that we can send API calls
	app.Prepare(scene);

	scene->Initialize();

	// -- Start

	// - Load texture
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
	tilemap->position = Vector2(gameConfig.PPU/2, gameConfig.PPU/2);

	TilemapComponent* tilemapTilemap = new TilemapComponent(tilemap);

	tilemapTilemap
		->SetTilemap(Resources::GetTilemap("tilesheet"))
		->Set(Resources::GetTexture("tilesheet"))
		->Bind(scene->renderer);


	// - Create player
	GameObject* player = scene->CreateGameObject();
	player->position = { 17,17 };
	player->scale = { 2,2 };
	
	SpriteComponent* playerSprite = new SpriteComponent(player);
	
	playerSprite
		->Set(Resources::GetTexture("player"))
		->AnimationSpeed(8);

	//CharacterControllerComponent* playerController = new CharacterControllerComponent();
	//player->AddComponent(playerController);

	TileLockedCharacterController* playerController = new TileLockedCharacterController(player);
	playerController->SetSpeed(8 * gameConfig.PPU);
	playerController->SetTilemap(tilemapTilemap);

	WarpComponent* playerWarp = new WarpComponent(player);
	playerWarp->SetOffset(player->scale * gameConfig.PPU);

	BoxColliderComponent* playerCollider = new BoxColliderComponent(player);
	playerCollider->Bind(scene);

	PlayerCollisionEventManager* playerColliderEventMng = new PlayerCollisionEventManager(player);
	playerColliderEventMng->Bind(playerCollider);




	return app.Run(scene);

	/*

	//* Create the Player
	GameObject* player = new GameObject();
	player->position = Vector2(100, 100);
	AddGameObject(player);

	SpriteComponent* playerSprite = new SpriteComponent(player);
	
	playerSprite
		->Set(Resources::GetTexture("player"))
		->AnimationSpeed(4);

	AddComponent(playerSprite);

	CharacterControllerComponent* playerController = new CharacterControllerComponent(player);
	AddComponent(playerController);

	WarpComponent* playerWarp = new WarpComponent(player);
	AddComponent(playerWarp);

	BoxColliderComponent* playerCollider = new BoxColliderComponent(player);
	playerCollider->Bind(*this);
	AddComponent(playerCollider);

	PlayerCollisionEventManager* playerColliderEventMng = new PlayerCollisionEventManager(player);
	playerColliderEventMng->Bind(playerCollider);
	AddComponent(playerColliderEventMng);

	return;

	// Yikes
	//player->GetComponent("SpriteComponent")
	//cout << "Sprite Component === " << player->GetComponent("SpriteComponent");



	//* Create the Ghost
	GameObject* ghost = new GameObject();
	ghost->position = Vector2(100, 100);
	AddGameObject(ghost);

	SpriteComponent* ghostSprite = new SpriteComponent(ghost);

	ghostSprite
		->Set(Resources::GetTexture("ghost"))
		->AnimationSpeed(2);

	AddComponent(ghostSprite);


	BoxColliderComponent* ghostCollider = new BoxColliderComponent(ghost);

	ghostCollider
		->Bind(*this)
		->SetSize(200);

	AddComponent(ghostCollider);




	//* Create the Pip
	GameObject* pip = new GameObject();
	pip->position = Vector2(300, 300);
	//pip->scale = 1;
	AddGameObject(pip);

	SpriteComponent* pipSprite = new SpriteComponent(pip);

	pipSprite
		->Set(Resources::GetTexture("pip"))
		->AnimationSpeed(2);

	AddComponent(pipSprite);




	//* Create the Cherry
	GameObject* cherry = new GameObject();
	cherry->position = Vector2(400, 300);
	AddGameObject(cherry);

	SpriteComponent* cherrySprite = new SpriteComponent(cherry);

	cherrySprite
		->Set(Resources::GetTexture("cherry"))
		->AnimationSpeed(2);

	AddComponent(cherrySprite);


	
	GameObject* ghost = new GameObject();
	ghost->position = Vector2(100, 100);

	SpriteComponent* ghostSprite = new SpriteComponent(ghost);
	ghostSprite->Set(Resources::GetTexture("ghost"));
	ghost->AddComponent(ghostSprite);
	AddComponent(ghostSprite);

	AddGameObject(ghost);



	/* Create a Pip
	Pip* pip = new Pip();
	pip->position = Vector2(100, 300);
	pip->sprite = Resources::GetTexture("pip");
	AddGameObject(pip);
	
	*/
}