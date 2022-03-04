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
#include "LockComponent.h"

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

	// - Load Resources
	Resources::LoadTexture("assets/textures/Capybara.png", true, "capybara");
	Resources::LoadTexture("assets/textures/Shadow.png", true, "shadow");

	//Resources::LoadTilemap("assets/tilemaps/Pacman.tmx", "tilesheet");
	//Resources::LoadWav("assets/audio/Venus by SketchyLogic.wav", "venus");


	// - Create audio
	//GameObject* audi = scene->CreateGameObject();

	//AudioSourceComponent* audiComp = new AudioSourceComponent(audi);
	//audiComp->Attach(Resources::GetWav("beginning"));

	//audiComp->source->Play();
	//while (source->IsPlaying()) ;
	//cout << "No longer playing" << endl;


	// SHADOW

	Engine::GameObject* shadowGO = scene->CreateGameObject();

	SpriteComponent* spriteComponent = new SpriteComponent(shadowGO);
	spriteComponent
		->Set(Resources::GetTexture("shadow"))
		->SetColour({ 0,0,0,128 });
	LockComponent* lockComponent = new LockComponent(shadowGO);

	// CAPYBARA

	Engine::GameObject* playerGO = scene->CreateGameObject();
	playerGO->position = Vector2(0, 0);
	playerGO->scale = Vector2(4, 4);

	SpriteComponent* playerSprite = new SpriteComponent(playerGO);
	playerSprite
		->Set(Resources::GetTexture("capybara"))
		->AnimationSpeed(8)
		->SetColour({ 255,255,255 });

	WalkComponent* playerWalk = new WalkComponent(playerGO);

	TargetMouseComponent* targetMouse = new TargetMouseComponent(playerGO);
	targetMouse->Bind(playerWalk);


	// LINK
	lockComponent->SetTarget(playerGO);

	// Mainloop
	return app.Run(scene);
}