#include "Muncher.h"

Muncher::Muncher(GameObject* gameObject, std::string name) : Component(gameObject, name)
{
}

Muncher* Muncher::SetTilemap(TilemapComponent* tilemapComponent)
{
	tilemapComp = tilemapComponent;
	return this;
}

Muncher* Muncher::SetScore(ScoreTracker* scoreTracker)
{
	this->scoreTracker = scoreTracker;
	return this;
}

void Muncher::Update(double delta, Engine::Scene& game)
{
	Vector2 tilePosition = tilemapComp->GetTilePositionAtScenePosition(gameObject->position);
	
	if (tilemapComp->tilemap.layers[1].IsTile(tilePosition))
	{
		Tilemaps::Tile tileAtCurrentPosition = tilemapComp->tilemap.layers[1].GetTile(tilePosition);

		if (tileAtCurrentPosition.id == 10) 
		{
			tilemapComp->tilemap.layers[1].DeleteTile(tileAtCurrentPosition);
			scoreTracker->score++;
		}
	}
	//cout << tileAtCurrentPosition << endl;
}
