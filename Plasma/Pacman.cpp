// By @ByCubed7 on Twitter

#include "Pacman.h"

#include "Engine/Resources.h"
#include "Engine/TextRenderer.h"
#include "Engine/Settings.h"

#include "Engine/Component.h"
#include "Engine/SpriteComponent.h"
#include "Engine/CharacterControllerComponent.h"
#include "Engine/TilemapComponent.h"
#include "Engine/BoxColliderComponent.h"

#include "WarpComponent.h"
#include "PlayerCollisionEventManager.h"

Pacman::Pacman(const Settings& setting) : Game(setting)
{
	state = Game::State::ACTIVE;
	input = Input();
	width = setting.screenWidth;
	height = setting.screenHeight;
}

Pacman::~Pacman() 
{
	//delete renderer;
	//delete text;
	//delete gameObjects;
}

void Pacman::Init()
{
	// Load textures
	Resources::LoadTexture("assets/textures/Player.png", true, "player");
	Resources::LoadTexture("assets/textures/Ghost.png", true, "ghost");
	Resources::LoadTexture("assets/textures/Pip.png", true, "pip");
	Resources::LoadTexture("assets/textures/Cherry.png", true, "cherry");
	Resources::LoadTexture("assets/textures/Tilesheet.png", true, "tilesheet");


	// Load levels
	Resources::LoadTilemap("assets/tilemaps/Pacman.tmx", "tilesheet");

	// Move this to start? \/

	//* Create the tilemap
	GameObject* tilemap = new GameObject();
	tilemap->position = Vector2(0, 0);
	//tilemap->scale = Vector2(0.5f);
	AddGameObject(tilemap);

	TilemapComponent* tilemapTilemap = new TilemapComponent(tilemap);

	tilemapTilemap
		->Set(Resources::GetTexture("tilesheet"))
		->Bind(renderer);
	AddComponent(tilemapTilemap);

	/*
	SpriteComponent* tilemapSprite = new SpriteComponent(tilemap);

	tilemapSprite
		->Set(Resources::GetTexture("pip"));

	AddComponent(tilemapSprite);
	//*/

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
	//*/

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


	
	/*GameObject* ghost = new GameObject();
	ghost->position = Vector2(100, 100);

	SpriteComponent* ghostSprite = new SpriteComponent(ghost);
	ghostSprite->Set(Resources::GetTexture("ghost"));
	ghost->AddComponent(ghostSprite);
	AddComponent(ghostSprite);

	AddGameObject(ghost);*/
	//*/



	/* Create a Pip
	Pip* pip = new Pip();
	pip->position = Vector2(100, 300);
	pip->sprite = Resources::GetTexture("pip");
	AddGameObject(pip);
	//*/
}

void Pacman::Update(double delta)
{
	// Process Game State
	if (state == State::PAUSED) timeStep = 0;
	else timeStep = 1.0f;

	//std::cout << timeStep << std::endl;

	//if (0)//gameObjects[0]->GetBounds().Overlaps(gameObjects[1]->GetBounds()))
	//{
	//	AABB go1 = gameObjects[0]->GetBounds();
	//	AABB go2 = gameObjects[1]->GetBounds();
	//	std::cout <<
	//		go1.lowerBound.ToString() << ":" << go2.upperBound.ToString() << " with " <<
	//		go2.lowerBound.ToString() << ":" << go1.upperBound.ToString() << std::endl;
	//}

}

void Pacman::Render() 
{
	//Renderer->DrawText("ahhhh", { 50, 100 }, 1, { 1, 1, 1 });
	if (state == State::PAUSED) renderer->text.RenderText("PAUSED", width / 2, height / 2, 1.0f, { 0.5f, 0.5f }, { 0.2f, 0.8, 0.2f });
}