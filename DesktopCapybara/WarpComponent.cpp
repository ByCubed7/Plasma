// By @ByCubed7 on Twitter

#include "WarpComponent.h"
#include "All.h"


WarpComponent::WarpComponent(Engine::GameObject* gameObject, std::string name)
    : Component(gameObject, name)
{
    warpX = true;
    warpY = true;
}

void WarpComponent::update(double time, double delta, Engine::Scene& game)
{
    if (warpX) {
        int maxLeftSide = game.app->getSize().x + offset.x - gameObject->scale.x;
        
        if (gameObject->position.x < 0 - offset.x) gameObject->position.x = maxLeftSide;
        if (gameObject->position.x > maxLeftSide) gameObject->position.x = 0 - offset.x;
    }

    if (warpY) {
        int maxTopSide = game.app->getSize().y + offset.y - gameObject->scale.y;

        if (gameObject->position.y < 0 - offset.x) gameObject->position.y = maxTopSide;
        if (gameObject->position.y > maxTopSide) gameObject->position.y = 0 - offset.x;
    }
}

WarpComponent* WarpComponent::Set(bool warpX, bool warpY) 
{
    this->warpX = warpX;
    this->warpY = warpY;

    return this;
}

WarpComponent* WarpComponent::SetOffset(Vector2 offset)
{
    this->offset = offset;
    return this;
}
