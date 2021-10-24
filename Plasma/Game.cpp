#include "game.h"
#include "Settings.h"
#include "Resources.h"
#include "SpriteRenderer.h"

#include "Shader.h"
#include "Texture.h"

#include <glm/fwd.hpp>
#include "Library/glad.h"
#include <GLFW/glfw3.h>
#include "TextRenderer.h"

#include "Player.h"
#include "Ghost.h"

SpriteRenderer* Renderer;
TextRenderer* Text;

Game::Game(const Settings& setting)
{
	state = Game::State::ACTIVE;
	input = Input();
	width = setting.screenWidth;
	height = setting.screenHeight;
}

Game::~Game()
{
	delete Renderer;
	//delete gameObjects;
}

void Game::AddGameObject(GameObject* gameObject)
{
	gameObjects.emplace_back(std::unique_ptr<GameObject>(gameObject));
}

void Game::Init()
{
	// - Load shaders
	Resources::LoadShader("assets/shaders/sprite.vs", "assets/shaders/sprite.frag", nullptr, "sprite");
	Resources::LoadShader("assets/shaders/text.vs", "assets/shaders/text.frag", nullptr, "text");

	// - Configure shaders
	Resources::GetShader("sprite").Use().SetInteger("image", 0);

	// As this is 2D we don't have to worry about perspective, use orthographic projection
	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->width), static_cast<float>(this->height), 0.0f, -1.0f, 1.0f);
	Resources::GetShader("sprite").SetMatrix4("projection", projection);

	// set render-specific controls
	Renderer = new SpriteRenderer(Resources::GetShader("sprite"));

	// Load Fonts
	Text = new TextRenderer(this->width, this->height);
	Text->Load("assets/fonts/arial.ttf", 24);

	// Load textures
	Resources::LoadTexture("assets/textures/Player.png", true, "player");
	Resources::LoadTexture("assets/textures/Ghost.png", true, "ghost");
	Resources::LoadTexture("assets/textures/Pip.png", true, "pip");

	// Load levels

	//* Create the Player
	Player* player = new Player();
	player->position = Vector2(100, 100);
	player->SetSprite(Resources::GetTexture("player"));
	AddGameObject(player);
	//*/

	//* Create the Ghost
	Ghost* ghost = new Ghost();
	ghost->position = Vector2(100, 100);
	ghost->SetSprite(Resources::GetTexture("ghost"));
	AddGameObject(ghost);
	//*/

	/* Create a Pip
	Pip* pip = new Pip();
	pip->position = Vector2(100, 300);
	pip->sprite = Resources::GetTexture("pip");
	AddGameObject(pip);
	//*/
}

void Game::Update(double delta)
{
	// Process Game State
	if (state == State::PAUSED) timeStep = 0;
	else timeStep = 1.0f;

	//std::cout << timeStep << std::endl;
	
	if (gameObjects[0]->GetBounds().Overlaps(gameObjects[1]->GetBounds()))
	{
		AABB go1 = gameObjects[0]->GetBounds();
		AABB go2 = gameObjects[1]->GetBounds();
		std::cout << 
			go1.lowerBound.ToString() << ":" << go1.upperBound.ToString() << " with " << 
			go2.lowerBound.ToString() << ":" << go2.upperBound.ToString() << std::endl;
	}

	// - IF PAUSED, DO NOTHING!
	if (state != State::ACTIVE) return;

	for (std::unique_ptr<GameObject>& gameObject : gameObjects) {

		// Compute physics
		Vector2 deltaVelo = Vector2(gameObject->velocity);
		deltaVelo.x *= delta;
		deltaVelo.y *= delta;

		gameObject->position = gameObject->position + deltaVelo;
		gameObject->rotation += gameObject->angularVelocity * delta;

		//std::cout << "Gameobject is at: " << gameObject->position.x << " : " << gameObject->position.y << std::endl;
		//std::cout << "Input: " << input.GetMousePosition().ToString() << std::endl;

		// Collision detection?

	}

	//*
	for (std::unique_ptr<GameObject>& gameObject : gameObjects)
	{
		gameObject->Update(delta, *this);
	}
	//*/
}

void Game::ProcessInput(double dt)
{
	// If the escape key is pressed, set the game to closing
	if (input.IsKey(input.Key_Escape))
		state = State::CLOSING;
	
	if (input.IsKeyDown(input.Key_P))
		state = state == State::ACTIVE ? State::PAUSED : State::ACTIVE;

	//std::cout << input.IsKeyDown(input.Key_P);

	input.Tick();
}

void Game::Render()
{
	//Renderer->DrawSprite(Resources::GetTexture("Player"),
	//    glm::vec2(300.0f, 300.0f), glm::vec2(400.0f, 400.0f), 75.0f, glm::vec3(0.5f, 0.5f, 0.0f));

	//*
	
	for (std::unique_ptr<GameObject>& gameObject : gameObjects)
	{
		gameObject->Draw(*Renderer);
	}
	//*/

	//Renderer->DrawText("ahhhh", { 50, 100 }, 1, { 1, 1, 1 });
	if (state == State::PAUSED) Text->RenderText("PAUSED", width / 2, height / 2, 1.0f, { 0.5f, 0.5f }, { 0.2f, 0.8, 0.2f });

}