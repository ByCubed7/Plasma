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

    isSolid = false;
    destroyed = false;
}

GameObject::GameObject(Vector2 position, float rotation, Vector2 scale, Vector2 velocity, float angularVelocity, Texture2D sprite, glm::vec3 color)
    : Object("GameObject")
{
    this->position = position;
    this->rotation = rotation;
    this->scale = scale;

    this->isSolid = false;
    this->destroyed = false;
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