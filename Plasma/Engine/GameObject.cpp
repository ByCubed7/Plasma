// By @ByCubed7 on Twitter

//
//#define VERBOSE

#include "GameObject.h"
#include "Component.h"
#include "Scene.h"

namespace Engine
{
    GameObject::GameObject(Engine::Scene* scene)
        : Object("GameObject")
    {
        this->scene = scene;

        position = 0;
        rotation = 0;
        scale = 1;

        isSolid = false;
        destroyed = false;
    }

    Vector2& GameObject::GetPosition() { return position; }
    float&   GameObject::GetRotation() { return rotation; }
    Vector2& GameObject::GetScale()    { return scale; }

    GameObject* GameObject::SetPosition(Vector2 value) { position = value; return this; }
    GameObject* GameObject::SetRotation(float value)   { rotation = value; return this; }
    GameObject* GameObject::SetScale(Vector2 value)    { scale = value; return this; }


    void GameObject::AddTag(std::string tag)
    {
        tags.insert(tag);
    }

    void GameObject::RemoveTag(std::string tag)
    {
        tags.erase(tag);
    }

    bool GameObject::HasTag(std::string tag)
    {
        return tags.find(tag) != tags.end();
    }


    Component* GameObject::addComponent(Component* component)
    {
        components.insert(component);
        //component->gameObject = this;
        scene->addComponent(component);
        return component;
    }

    void GameObject::removeComponent(Component* component) { components.erase(component); }


    Component* GameObject::getComponent(std::string componentName)
    {
        for (Component* component : components)
        {
            if (component->ToString() == componentName)
                return component;
        }

        return nullptr;
    }

    bool GameObject::hasComponent(std::string componentName)
    {
        for (Component* component : components)
        {
            if (component->ToString() == componentName)
                return true;
        }

        return false;
    }

    GameObject::operator bool() { return !destroyed; }

}