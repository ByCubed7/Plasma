// By @ByCubed7 on Twitter

//#include "All.h"
//#define VERBOSE

#include "Core.h"
#include "Components.h"
#include "Tilemaps.h"
#include "Render.h"
#include "Audio.h"
#include "UI.h"

#include "WarpComponent.h"
#include "WalkComponent.h"
#include "TargetMouseComponent.h"

#include <GLFW/glfw3.h>

#include <iostream>

#include <windows.h>
#include <tchar.h>


int main(int argc, char* argv[])
{
	FreeConsole();
	Engine::App app = Engine::App();
	Engine::Scene* scene = app.CreateGame();
	//Scene scene = pacman.scene; // Get the default scene

	// Prepares an OpenGL context so that we can send API calls
	app.Build(scene);

	scene->Load();

	// - Load textures
	Resources::LoadTexture("assets/textures/Capybara.png", true, "capybara");

	// Load levels
	Resources::LoadTilemap("assets/tilemaps/Pacman.tmx", "tilesheet");
	Resources::LoadWav("assets/audio/Venus by SketchyLogic.wav", "venus");	
	Resources::LoadWav("assets/audio/beginning.wav", "beginning");


	// - Create audio
	//GameObject* audi = scene->CreateGameObject();

	//AudioSourceComponent* audiComp = new AudioSourceComponent(audi);
	//audiComp->Attach(Resources::GetWav("beginning"));

	//audiComp->source->Play();
	//while (source->IsPlaying()) ;
	//cout << "No longer playing" << endl;

	Engine::GameObject* playerGO = scene->CreateGameObject();
	playerGO->position = Vector2(0, 0);
	playerGO->scale = Vector2(4, 4);

	SpriteComponent* spriteComponent = new SpriteComponent(playerGO);
	spriteComponent
		->Set(Resources::GetTexture("capybara"))
		->AnimationSpeed(8)
		->SetColour({ 255,255,255 });

	WalkComponent* walkComponent = new WalkComponent(playerGO);

	TargetMouseComponent* targetMouseComponent = new TargetMouseComponent(playerGO);
	targetMouseComponent->Bind(walkComponent);

	// Mainloop
	return app.Run(scene);
}