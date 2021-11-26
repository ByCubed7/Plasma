// By @ByCubed7 on Twitter

#pragma once

#include "Engine/Settings.h"
#include "Engine/Game.h"

class Pacman : public Game
{
public:
	// Constructor
	Pacman(const Settings& setting);

	// Destructor
	~Pacman();

	void Init() override;
	void Update(double delta) override;
	void Render() override;
};

