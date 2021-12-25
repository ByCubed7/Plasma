#include "ScoreTracker.h"

#include "Engine/Tilemaps/Tile.h"

ScoreTracker::ScoreTracker(GameObject* gameObject, std::string name)
	: Component(gameObject, name)
{
	score = 10;
}

ScoreTracker* ScoreTracker::SetTextbox(UI::TextboxComponent* textboxComponent)
{
	textbox = textboxComponent;
	return this;
}

void ScoreTracker::Update(double delta, Engine::Scene& game)
{
	textbox->text = "Score: " + std::to_string(score);
}
