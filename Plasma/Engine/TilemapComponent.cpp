// By @ByCubed7 on Twitter

#include "TilemapComponent.h"

TilemapComponent::TilemapComponent(GameObject* gameObject, std::string name)
    : Component(gameObject, name)
{
    //cout << "2 TilemapComponent::TilemapComponent" << endl;
    tilemap = Tilemap();
    //tilemap.AddTile({ 0, 0 }, 0);
    tilemap.AddTile({ 0, 0 }, 0);
    tilemap.AddTile({ 0, 0 }, 1);
    tilemap.AddTile({ -1, 0 }, 2);
    tilemap.AddTile({ 0, 1 }, 2);
    tilemap.AddTile({ 1, -1 }, 0);

    color = { 1, 1, 1 };
    animationSpeed = 2;
}

void TilemapComponent::Draw(Renderer& renderer)
{
    int PPU(Settings::PPU);

    renderer.tilemap.Update(tilemap.GetRenderData());

    renderer.tilemap.DrawTilemap(
        tilemap.tileSheet,
        { gameObject->position.x, gameObject->position.y },
        { gameObject->scale.x * PPU, gameObject->scale.y * PPU },
        gameObject->rotation,
        spriteFrame,
        { 1, 1, 1 }
    );
}

void TilemapComponent::Update(double delta, Game& game)
{
    //*
    animationPoint += delta;
    spriteFrame = animationPoint * animationSpeed;
    //*/
}

TilemapComponent* TilemapComponent::Bind(Renderer* renderer)
{
    //cout << "3 TilemapComponent::Bind" << endl;
    //cout << "tilemap.Count(): " << tilemap.Count() << endl;
    

    // Bad Cubie, use cacheing here
    renderer->tilemap.Update(tilemap.GetRenderData());

    return this;
}

TilemapComponent* TilemapComponent::Set(Texture2D tileSheet) 
{ 
    tilemap.tileSheet = tileSheet; 
    return this; 
}

TilemapComponent* TilemapComponent::SetTileSize(pair<int, int> size) { this->tilemap.tileSize = size; return this; }