#include "TilemapComponent.h"

TilemapComponent::TilemapComponent(GameObject* gameObject, std::string name)
    : Component(gameObject, name)
{
}

void TilemapComponent::Draw(Renderer& renderer)
{
    int PPU(Settings::PPU);

    renderer.tilemap.DrawTilemap(
        { gameObject->position.x, gameObject->position.y },
        { gameObject->scale.x * PPU, gameObject->scale.y * PPU },
        gameObject->rotation,
        0,
        { 1,1,1 }
    );
    /*
    glm::vec2 drawScale = { gameObject->scale.x * PPU, gameObject->scale.y * PPU };
    glm::vec2 pos = { gameObject->position.x, gameObject->position.y };

    renderer.sprite.DrawSprite(
        this->sprite,
        pos,
        drawScale,
        gameObject->rotation,
        spriteFrame,
        color
    );
    */
}

void TilemapComponent::Update(double delta, Game& game)
{
    /*
    animationPoint += delta;
    spriteFrame = animationPoint * animationSpeed;
    */
}