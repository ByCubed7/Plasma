#include "game.h"

#include "Settings.h"
#include "Resources.h"
#include "SpriteRenderer.h"
#include "TextRenderer.h"
#include "Shader.h"
#include "Texture.h"
#include "GameObject.h"

#include <glm/fwd.hpp>
#include "../Library/glad.h"
#include <GLFW/glfw3.h>

Game::Game(const Settings& setting)
{
	state = Game::State::ACTIVE;
	input = Input();
	width = setting.screenWidth;
	height = setting.screenHeight;
}

Game::~Game()
{
	delete renderer;
	//delete gameObjects;
}

void Game::AddGameObject(GameObject* gameObject)
{
	gameObjects.emplace_back(std::unique_ptr<GameObject>(gameObject));
}

void Game::GInit()
{
	// As this is 2D we don't have to worry about perspective, use orthographic projection
	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->width), static_cast<float>(this->height), 0.0f, -1.0f, 1.0f);

	// - Load and Config shaders

	// Sprite
	Shader ShaderSprite = Resources::LoadShader("assets/shaders/sprite.vs", "assets/shaders/sprite.frag", nullptr, "sprite");
	ShaderSprite.Use().SetInteger("image", 0);
	ShaderSprite.SetMatrix4("projection", projection);
	//ShaderSprite.SetVector2("index", 1, 0);
	ShaderSprite.SetInteger("index", 1);
	
	// Text
	Shader ShaderText = Resources::LoadShader("assets/shaders/text.vs", "assets/shaders/text.frag", nullptr, "text");
	ShaderText.Use().SetInteger("text", 0);
	ShaderText.SetMatrix4("projection", projection);
	

	// - Load Renderer(s)

	renderer = new Renderer(Resources::GetShader("sprite"), Resources::GetShader("text"));
	//renderer = new SpriteRenderer(Resources::GetShader("sprite"));
	//text = new TextRenderer(Resources::GetShader("text"));


	// - Load Text Fonts
	
	Resources::LoadFont("assets/fonts/arial.ttf", "arial");

	//text->Load("assets/fonts/arial.ttf", 24);


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

void Game::GUpdate(double delta) 
{
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

void Game::GRender()
{
	//Renderer->DrawSprite(Resources::GetTexture("Player"),
	//    glm::vec2(300.0f, 300.0f), glm::vec2(400.0f, 400.0f), 75.0f, glm::vec3(0.5f, 0.5f, 0.0f));

	//*
	for (std::unique_ptr<GameObject>& gameObject : gameObjects)
	{
		gameObject->Draw(*renderer);
	}
	//*/

}


// -- To be overloaded --

void Game::Init() {}
void Game::Update(double delta) {}
void Game::Render() {}