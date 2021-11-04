#include "GameObject.h"
#include "Settings.h"
#include "Game.h"
#include "Component.h"

#include <typeinfo>

GameObject::GameObject()
    : Object("GameObject")
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

    spriteFrame = 0;
    spriteSize = 1024;
}

GameObject::GameObject(Vector2 position, float rotation, Vector2 scale, Vector2 velocity, float angularVelocity, Texture2D sprite, glm::vec3 color)
    : Object("GameObject")
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

    CalcBounds();
}

void GameObject::AddComponent(Component* component) { components.push_back(component); }
void GameObject::RemoveComponent(Component* component) { components.remove(component); }

template<typename T> Component* GameObject::GetComponent() 
{
    for (Component* componentIn : components) {
        if (typeid(componentIn) == typeid(T))
            return componentIn;
    }

    return nullptr;
}

// Set Get Sprite
void GameObject::SetSprite(Texture2D sprite) 
{ 
    this->sprite = sprite; 
    CalcBounds();
}
Texture2D GameObject::GetSprite() { return this->sprite; }

AABB GameObject::GetBounds()
{
    return { position + bounds.lowerBound, position + bounds.upperBound };
}

void GameObject::CalcBounds() 
{
    // Update bounds
    Vector2 upperBound = Vector2(Settings::PPU, Settings::PPU) / 2;
    Vector2 lowerBound = Vector2(-Settings::PPU, -Settings::PPU) / 2;
    this->bounds = AABB(lowerBound, upperBound);
}

void GameObject::Draw(Renderer& renderer)
{
    // Draw all of the components
    //for (Component* component : components) component->Draw(renderer);

    int PPU(Settings::PPU);
    glm::vec2 drawScale = { this->scale.x * PPU, this->scale.y * PPU };
    glm::vec2 pos = { position.x, position.y };

    renderer.DrawSprite(
        this->sprite, 
        pos,
        drawScale,
        this->rotation, 
        spriteFrame,
        this->color
    );
}

void GameObject::Update(double delta, Game& game)
{
    // ¯\_(ツ)_/¯
}