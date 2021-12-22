#include "Muncher.h"

Muncher::Muncher(GameObject* gameObject, std::string name) : Component(gameObject, name)
{
}

Muncher* Muncher::SetTilemap(TilemapComponent* tilemapComponent)
{
	tilemapComp = tilemapComponent;
	return this;
}

void Muncher::Update(double delta, Engine::Scene& game)
{
	//Vector2 tilePosition = tilemapComp->GetTilePositionAtScenePosition(gameObject->position) + 0.5f;
	//int tileAtCurrentPosition = tilemapComp->tilemap.layers[1].GetTileAt(tilePosition);

	//tilemapComp->tilemap.layers[1].GetTileAt();

	//cout << tileAtCurrentPosition << endl;
}
