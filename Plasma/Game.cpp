#include "game.h"
#include "Settings.h"

Game::Game(const Settings& setting) : State(GAME_ACTIVE), Keys(), Width(setting.screenWidth), Height(setting.screenHeight)
{

}

Game::~Game()
{

}

void Game::Init()
{

}

void Game::Update(float dt)
{

}

void Game::ProcessInput(float dt)
{

}

void Game::Render()
{

}