// By @ByCubed7 on Twitter

#include "Component.h"
#include "Object.h"

Component::Component(std::string name)
    : Object(name)
{}

void Component::Update(double delta, Engine::Scene& game) {}
void Component::Draw(Render::Renderers& renderer) {}
