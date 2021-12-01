// By @ByCubed7 on Twitter

#include "TilemapComponent.h"

TilemapComponent::TilemapComponent(GameObject* gameObject, std::string name)
    : Component(gameObject, name)
{
    //tilemap = Resources::GetTilemap("tilesheet");

    //cout << "2 TilemapComponent::TilemapComponent" << endl;
    //tilemap = Tilemaps::Tilemap();
    //tilemap.AddLayer(Tilemaps::TileLayer());
    //tilemap.AddTile({ 0, 0 }, 0);
    /*
    tilemap.AddTile(0, 1, { 0, 0 }, 0, { 1, 1 });
    tilemap.AddTile(0, 2, { -1, 0 });
    tilemap.AddTile(0, 2, { 0, 1 });
    tilemap.AddTile(0, 0, { 1, -1 });
    //*/
    color = { 1, 1, 1 };
    animationSpeed = 2;
}

void TilemapComponent::Draw(Renderers& renderer)
{
    int PPU(Settings::PPU);

    /*for (auto& tile : tilemap.tiles) {
        tile.rotation += 1;
        cout << tile.rotation << endl;
    //}*/

    Tilemaps::TileLayer& layer = tilemap.layers[0];
    renderer.tilemap.Update(layer.GetRender());

    renderer.tilemap.DrawTileLayer(
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

TilemapComponent* TilemapComponent::Bind(Renderers* renderer)
{
    //cout << "3 TilemapComponent::Bind" << endl;
    //cout << "tilemap.Count(): " << tilemap.Count() << endl;
    

    // Bad Cubie, use cacheing here
    Tilemaps::TileLayer& layer = tilemap.layers[0];
    renderer->tilemap.Update(layer.GetRender());

    return this;
}

TilemapComponent* TilemapComponent::Set(Texture2D tileSheet) 
{ 
    tilemap.tileSheet = tileSheet; 
    return this; 
}

TilemapComponent* TilemapComponent::SetTilemap(const Tilemaps::Tilemap& newTilemap)
{
    tilemap = newTilemap;
    return this;
}

TilemapComponent* TilemapComponent::SetTileSize(pair<int, int> size) { this->tilemap.tileSize = size; return this; }
