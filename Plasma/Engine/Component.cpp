// By @ByCubed7 on Twitter

#include "All.h"
//#define VERBOSE

#include "Component.h"

#include "GameObject.h"
#include "Object.h"
#include "Scene.h"
#include "Render/Renderers.h"

namespace Engine 
{
    Component::Component(GameObject* gameObject, std::string name)
        : Object(name)
    {
        this->gameObject = gameObject;
        this->scene = gameObject->scene;

        gameObject->AddComponent(this);
    }

    void Component::Update(double time, double delta, Engine::Scene& game) {}
    void Component::Draw(Render::Renderers& renderer) {}
}