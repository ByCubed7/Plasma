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

void TilemapComponent::update(double time, double delta, Engine::Scene& game)
{
    animationPoint += delta;
    spriteFrame = (int)animationPoint * animationSpeed;
}

void TilemapComponent::draw(Render::Renderers& renderer)
{
    for (auto& layer : tilemap.layers)
    {
        renderer.tilemap.update(layer.GetRender());

        renderer.tilemap.DrawTileLayer(
            tilemap.tileSheet,
            { gameObject->position.x, gameObject->position.y },
            { gameObject->scale.x, gameObject->scale.y },
            gameObject->rotation,
            spriteFrame,
            { 1, 1, 1 }
        );
    }
    //*/
}

TilemapComponent* TilemapComponent::bind(Render::Renderers* renderer)
{
    // Bad Cubie, use cacheing here
    renderer->tilemap.update(tilemap.layers[0].GetRender());

    return this;
}

TilemapComponent* TilemapComponent::setTexture2D(Texture2D tileSheet) 
{ 
    tilemap.tileSheet = tileSheet; 
    return this; 
}

TilemapComponent* TilemapComponent::setTilemap(const Tilemaps::Tilemap& newTilemap)
{
    tilemap = newTilemap;
    return this;
}

TilemapComponent* TilemapComponent::setTileSize(int size) { this->tilemap.tileSize = Vector2(size); return this; }

Vector2 TilemapComponent::getTilePositionAtScenePosition(Vector2 pos)
{
    // Transform position to gameobject
    pos += gameObject->position;
    pos.round(1);

    return pos;
}

Vector2 TilemapComponent::getScenePositionAtTilePosition(Vector2 pos)
{
    // Transform position to gameobject
    pos -= gameObject->position;
    return pos;
}

int TilemapComponent::getTileAtScenePosition(Vector2 pos)
{
    pos = getTilePositionAtScenePosition(pos);
    Vector2Int posInt = Vector2Int({ (int)pos.x, (int)pos.y });
    return tilemap.layers[0].GetTile(posInt).id;
}

bool TilemapComponent::isTileAtScenePosition(Vector2 pos) 
{
    Vector2Int posInt = Vector2Int({ (int)pos.x, (int)pos.y });
    return tilemap.layers[0].IsTile(posInt);
}