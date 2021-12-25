// By @ByCubed7 on Twitter

#pragma once

#include "Engine/Tilemaps/Tilemap.h"

#include "Engine/Vector2.h"
#include "Engine/Component.h"
#include "Engine/UI/TextboxComponent.h"

class ScoreTracker : public Component
{
public:
	ScoreTracker(GameObject* gameObject, std::string name = "MuncherComponent");

	UI::TextboxComponent* textbox;

	int score;

	ScoreTracker* SetTextbox(UI::TextboxComponent* textboxComponent);

	void Update(double delta, Engine::Scene& game) override;
};

