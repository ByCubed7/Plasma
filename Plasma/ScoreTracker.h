// By @ByCubed7 on Twitter

#pragma once

#include "Core.h"
#include "Components.h"
#include "UI.h"

class ScoreTracker : public Component
{
public:
	ScoreTracker(GameObject* gameObject, std::string name = "MuncherComponent");

	UI::TextboxComponent* textbox;

	int score;

	ScoreTracker* SetTextbox(UI::TextboxComponent* textboxComponent);

	void Update(double delta, Engine::Scene& game) override;
};

