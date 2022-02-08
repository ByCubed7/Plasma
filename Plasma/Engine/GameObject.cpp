// By @ByCubed7 on Twitter

#include "GameObject.h"

#include "Component.h"

#include <type_traits>

GameObject::GameObject(Engine::Scene* scene)
    : Object("GameObject")
{
    this->scene = scene;

    position = { 0.0f, 0.0f };
    rotation = 0.0f;
    scale = { 1.0f, 1.0f };

    isSolid = false;
    destroyed = false;
}
/*
GameObject::GameObject(Vector2 position, float rotation, Vector2 scale, Vector2 velocity, float angularVelocity, Texture2D sprite, glm::vec3 color)
    : Object("GameObject")
{
    this->position = position;
    this->rotation = rotation;
    this->scale = scale;

    this->isSolid = false;
    this->destroyed = false;
}
*/
Component* GameObject::AddComponent(Component* component)
{ 
    components.push_back(component);
    //component->gameObject = this;
    scene->AddComponent(component); 
    return component;
}

void GameObject::RemoveComponent(Component* component) { components.remove(component); }


Component* GameObject::GetComponent(std::string componentName)
{
    for (Component* component : components)
    {
        if (component->ToString() == componentName)
            return component;
    }

    return nullptr;
}

bool GameObject::HasComponent(std::string componentName)
{
    for (Component* component : components)
    {
        if (component->ToString() == componentName)
            return true;
    }

    return false;
}

GameObject::operator bool() { return !destroyed; }