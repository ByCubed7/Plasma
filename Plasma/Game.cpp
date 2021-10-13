#include "game.h"
#include "Settings.h"
#include "Resources.h"
#include "SpriteRenderer.h"

#include "Shader.h"
#include "Texture.h"

#include <glm/fwd.hpp>
#include "glad.h"
#include <GLFW/glfw3.h>

SpriteRenderer* Renderer;

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
    delete &gameObjects;
}

void Game::AddGameObject(GameObject gameObject)
{
    gameObjects.push_back(gameObject);
}

void Game::Init()
{
    // - Load shaders
    Resources::LoadShader("assets/shaders/sprite.vs", "assets/shaders/sprite.frag", nullptr, "sprite");
    
    // - Configure shaders
    Resources::GetShader("sprite").Use().SetInteger("image", 0);

    // As this is 2D we don't have to worry about perspective, use orthographic projection
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->width),
        static_cast<float>(this->height), 0.0f, -1.0f, 1.0f);
    Resources::GetShader("sprite").SetMatrix4("projection", projection);
    
    // set render-specific controls
    Renderer = new SpriteRenderer(Resources::GetShader("sprite"));
    
    // load textures
    Resources::LoadTexture("assets/textures/Player.png", true, "Player");

    // Load levels
    GameObject player = GameObject();
    player.position = glm::vec2(200, 100);
    player.velocity = glm::vec2(100, 0);
    player.sprite = Resources::GetTexture("Player");

    AddGameObject(player);
}

void Game::Update(double delta)
{
    for (GameObject& gameObject : gameObjects)
    {
        // Compute physics
        glm::vec2 deltaVelo = glm::vec2(gameObject.velocity);
        deltaVelo.x *= delta;
        deltaVelo.y *= delta;

        gameObject.position += deltaVelo;
        gameObject.rotation += gameObject.angularVelocity * delta;
        
        //std::cout << "Gameobject is at: " << gameObject.position.x << " : " << gameObject.position.y std::endl;

        // Collision detection?


    }
}

void Game::ProcessInput(double dt)
{
    // If the escape key is pressed, set the game to closing
    if (input.IsKey(input.Key_Escape))
        state = Game::State::CLOSING;
    
}

void Game::Render()
{
    //Renderer->DrawSprite(Resources::GetTexture("Player"),
    //    glm::vec2(300.0f, 300.0f), glm::vec2(400.0f, 400.0f), 75.0f, glm::vec3(0.5f, 0.5f, 0.0f));


    for (GameObject& gameObject : gameObjects)
    {
        gameObject.Draw(*Renderer);
    }
}