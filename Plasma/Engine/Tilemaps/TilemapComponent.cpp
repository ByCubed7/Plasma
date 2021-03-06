// By @ByCubed7 on Twitter


//#define VERBOSE

#include "TilemapComponent.h"
#include "../GameObject.h"
#include "../Window.h"

#include "../Render/Renderers.h"

TilemapComponent::TilemapComponent(Engine::GameObject* gameObject, std::string name)
    : Component(gameObject, name)
{
    animationPoint = 0;
    spriteFrame = 0;

    color = { 1, 1, 1 };
    animationSpeed = 2;
}

void TilemapComponent::Update(double time, double delta, Engine::Scene& game)
{
    //*
    animationPoint += delta;
    spriteFrame = (int)animationPoint * animationSpeed;
    //*/
}

void TilemapComponent::Draw(Render::Renderers& renderer)
{
    int ppu = gameObject->scene->GetWindow()->GetPPU();

    //for (auto& tile : tilemap.layers[0].tiles)
    //    tile.rotation += 1;


    for (auto& layer : tilemap.layers)
    {
        renderer.tilemap.Update(layer.GetRender());

        renderer.tilemap.DrawTileLayer(
            tilemap.tileSheet,
            { gameObject->position.x, gameObject->position.y },
            { gameObject->scale.x * ppu, gameObject->scale.y * ppu },
            gameObject->rotation,
            spriteFrame,
            { 1, 1, 1 }
        );
    }
    //*/
}

TilemapComponent* TilemapComponent::Bind(Render::Renderers* renderer)
{
    //cout << "3 TilemapComponent::Bind" << endl;
    //cout << "tilemap.Count(): " << tilemap.Count() << endl;
    

    // Bad Cubie, use cacheing here
    //renderer->tilemap.Update(tilemap.layers[0].GetRender());

    renderer->tilemap.Update(tilemap.layers[0].GetRender());

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

TilemapComponent* TilemapComponent::SetTileSize(int size) { this->tilemap.tileSize = Vector2(size); return this; }

Vector2 TilemapComponent::GetTilePositionAtScenePosition(Vector2 pos)
{
    // Transform position to gameobject
    pos += gameObject->position;
    pos /= GetTileDensity();
    pos.Round(1);

    return pos;
}

Vector2 TilemapComponent::GetScenePositionAtTilePosition(Vector2 pos)
{
    // Transform position to gameobject
    pos *= GetTileDensity();
    pos -= gameObject->position;
    return pos;
}


Vector2 TilemapComponent::GetTileDensity()
{
    // Scale position from PPU
    // Note: Also scale by gameobject scale
    return Vector2(gameObject->scene->GetWindow()->GetPPU());
}

int TilemapComponent::GetTileAtScenePosition(Vector2 pos)
{
    pos = GetTilePositionAtScenePosition(pos);
    Vector2Int posInt = Vector2Int({ (int)pos.x, (int)pos.y });
    return tilemap.layers[0].GetTile(posInt).id;
}

bool TilemapComponent::IsTileAtScenePosition(Vector2 pos) 
{
    Vector2Int posInt = Vector2Int({ (int)pos.x, (int)pos.y });
    return tilemap.layers[0].IsTile(posInt);
}