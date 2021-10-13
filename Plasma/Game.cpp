#include "game.h"
#include "Settings.h"
#include "Resources.h"
#include "SpriteRenderer.h"

#include "Shader.h"
#include "Texture.h"

#include <glm/fwd.hpp>

SpriteRenderer* Renderer;

Game::Game(const Settings& setting) : State(GameState::GAME_ACTIVE), Keys(), Width(setting.screenWidth), Height(setting.screenHeight)
{

}

Game::~Game()
{
    delete Renderer;
}


void Game::Init()
{

    // - Load shaders
    Resources::LoadShader("assets/shaders/sprite.vs", "assets/shaders/sprite.frag", nullptr, "sprite");
    
    // - Configure shaders
    Resources::GetShader("sprite").Use().SetInteger("image", 0);

    // As this is 2D we don't have to worry about perspective, use orthographic projection
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->Width),
        static_cast<float>(this->Height), 0.0f, -1.0f, 1.0f);
    Resources::GetShader("sprite").SetMatrix4("projection", projection);
    
    // set render-specific controls
    Renderer = new SpriteRenderer(Resources::GetShader("sprite"));
    
    // load textures
    Resources::LoadTexture("assets/textures/Player.png", true, "Player");

}

void Game::Update(float dt)
{

}

void Game::ProcessInput(float dt)
{

}

void Game::Render()
{
    Renderer->DrawSprite(Resources::GetTexture("Player"),
        glm::vec2(200.0f, 200.0f), glm::vec2(300.0f, 400.0f), 45.0f, glm::vec3(0.0f, 1.0f, 0.0f));
}