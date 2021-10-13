#include "GameObject.h"

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

GameObject::GameObject(glm::vec2 position, float rotation, glm::vec2 scale, glm::vec2 velocity, float angularVelocity, Texture2D sprite, glm::vec3 color)
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
    renderer.DrawSprite(this->sprite, this->position, this->scale, this->rotation, this->color);
}