// By @ByCubed7 on Twitter

#include "All.h"
#include "WarpComponent.h"
#include "Engine/Window.h"


WarpComponent::WarpComponent(Engine::GameObject* gameObject, std::string name)
    : Component(gameObject, name)
{
    warpX = true;
    warpY = true;
}

void WarpComponent::Update(double delta, Engine::Scene& game)
{
    int ppu = gameObject->scene->GetWindow()->GetPPU();

    if (warpX) {
        int maxLeftSide = game.app->GetSize().x + offset.x - gameObject->scale.x * ppu;
        
        if (gameObject->position.x < 0 - offset.x) gameObject->position.x = maxLeftSide;
        if (gameObject->position.x > maxLeftSide) gameObject->position.x = 0 - offset.x;
    }

    if (warpY) {
        int maxTopSide = game.app->GetSize().y + offset.y - gameObject->scale.y * ppu;

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
