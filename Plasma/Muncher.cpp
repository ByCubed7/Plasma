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
	Vector2 tilePosition = tilemapComp->GetTilePositionAtScenePosition(gameObject->position);
	int tileAtCurrentPosition = tilemapComp->tilemap.GetTileAt(1, std::pair<int, int>(tilePosition.x, tilePosition.y));

	cout << tileAtCurrentPosition << endl;
}
