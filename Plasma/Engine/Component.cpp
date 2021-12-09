// By @ByCubed7 on Twitter

#include "Component.h"
#include "Object.h"

Component::Component(GameObject* gameObject, std::string name)
    : Object(name)
{
    this->gameObject = gameObject;
    gameObject->AddComponent(this);
}

void Component::Update(double delta, Engine::Scene& game) {}
void Component::Draw(Render::Renderers& renderer) {}
