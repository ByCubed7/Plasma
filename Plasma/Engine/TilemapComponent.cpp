// By @ByCubed7 on Twitter

#include "TilemapComponent.h"

TilemapComponent::TilemapComponent(GameObject* gameObject, std::string name)
    : Component(gameObject, name)
{
    tilemap = Tilemap();
    color = { 1, 1, 1 };
}

void TilemapComponent::Draw(Renderer& renderer)
{
    int PPU(Settings::PPU);

    renderer.tilemap.DrawTilemap(
        tilemap.tileSheet,
        { gameObject->position.x, gameObject->position.y },
        { gameObject->scale.x * PPU, gameObject->scale.y * PPU },
        gameObject->rotation,
        0,
        {10,10,10}
    );
}

void TilemapComponent::Update(double delta, Game& game)
{
    /*
    animationPoint += delta;
    spriteFrame = animationPoint * animationSpeed;
    */
}

TilemapComponent* TilemapComponent::Bind(Renderer* renderer)
{
    //renderer->tilemap.Bind(&tilemap);
    return this;
}

TilemapComponent* TilemapComponent::Set(Texture2D tileSheet) 
{ 
    tilemap.tileSheet = tileSheet; 
    return this; 
}

TilemapComponent* TilemapComponent::SetTileSize(tuple<int, int> size) { this->tilemap.tileSize = size; return this; }