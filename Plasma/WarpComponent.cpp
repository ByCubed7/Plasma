// By @ByCubed7 on Twitter

#include "WarpComponent.h"


WarpComponent::WarpComponent(std::string name)
    : Component(name)
{
    warpX = true;
    warpY = true;

    
}


void WarpComponent::Update(double delta, Engine::Scene& game)
{
    if (warpX) {

        int maxLeftSide = game.width + offset.x - gameObject->scale.x * game.settings.PPU;
        
        if (gameObject->position.x < 0 - offset.x) gameObject->position.x = maxLeftSide;
        if (gameObject->position.x > maxLeftSide) gameObject->position.x = 0 - offset.x;
    }

    if (warpY) {
        int maxTopSide = game.height + offset.y - gameObject->scale.y * game.settings.PPU;

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
