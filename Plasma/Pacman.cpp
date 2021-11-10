#include "Pacman.h"

#include "Engine/Resources.h"
#include "Engine/TextRenderer.h"
#include "Engine/Settings.h"
#include "Engine/SpriteComponent.h"
#include "Engine/CharacterControllerComponent.h"
#include "Engine/Component.h"

#include "Ghost.h"

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

	// Load levels

	// Move this to start? \/

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

	// Yikes
	//player->GetComponent("SpriteComponent")
	//cout << "Sprite Component === " << player->GetComponent("SpriteComponent");

	
	//*/


	//* Create the Ghost
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
	if (state == State::PAUSED) renderer->RenderText("PAUSED", width / 2, height / 2, 1.0f, { 0.5f, 0.5f }, { 0.2f, 0.8, 0.2f });
}