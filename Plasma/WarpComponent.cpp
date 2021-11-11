#include "WarpComponent.h"


WarpComponent::WarpComponent(GameObject* gameObject, std::string name)
    : Component(gameObject, name)
{
    warpX = true;
    warpY = true;
}


void WarpComponent::Update(double delta, Game& game)
{
    if (warpX) {

        int maxLeftSide = game.width - gameObject->scale.x * game.settings->PPU;
        
        if (gameObject->position.x < 0) gameObject->position.x = maxLeftSide;
        if (gameObject->position.x > maxLeftSide) gameObject->position.x = 0;
    }

    if (warpY) {
        int maxTopSide = game.height - gameObject->scale.y * game.settings->PPU;

        if (gameObject->position.y < 0) gameObject->position.y = maxTopSide;
        if (gameObject->position.y > maxTopSide) gameObject->position.y = 0;
    }
}

WarpComponent* WarpComponent::Set(bool warpX, bool warpY) 
{
    this->warpX = warpX;
    this->warpY = warpY;

    return this;
}