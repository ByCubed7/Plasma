#include "Component.h"
#include "Object.h"

Component::Component(GameObject* gameObject, std::string name)
    : Object(name)
{
	this->gameObject = gameObject;
}

void Component::Update(double delta, Game& game) {}
void Component::Draw(Renderer& renderer) {}
