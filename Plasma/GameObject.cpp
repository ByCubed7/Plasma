#include "GameObject.h"
#include "Settings.h"
#include "Game.h"

GameObject::GameObject()
{
    position = { 0.0f, 0.0f };
    rotation = 0.0f;
    scale = { 1.0f, 1.0f };

    velocity = { 0.0f, 0.0f };
    angularVelocity = 0.0f;

    color = { 1.0f, 1.0f, 1.0f };
    sprite = Texture2D();

    isSolid = false;
    destroyed = false;
}

GameObject::GameObject(Vector2 position, float rotation, Vector2 scale, Vector2 velocity, float angularVelocity, Texture2D sprite, glm::vec3 color)
{
    this->position = position;
    this->rotation = rotation;
    this->scale = scale;
    
    this->velocity = velocity;
    this->angularVelocity = angularVelocity;

    this->sprite = sprite;
    this->color = color;

    this->isSolid = false;
    this->destroyed = false;
}

void GameObject::Draw(SpriteRenderer& renderer)
{
    int PPU(Settings::PPU);
    glm::vec2 drawScale = { this->scale.x * PPU, this->scale.y * PPU };
    glm::vec2 pos = { position.x, position.y };

    renderer.DrawSprite(
        this->sprite, 
        pos,
        drawScale,
        this->rotation, 
        this->color
    );
}

void GameObject::Update(double delta, Game& game)
{
    // ¯\_(ツ)_/¯
}