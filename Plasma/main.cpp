// By @ByCubed7 on Twitter

//#define VERBOSE

//#include "Core.h"
//#include "Components.h"
//#include "Tilemaps.h"
//#include "Render.h"
//#include "Audio.h"
//#include "UI.h"
#include "All.h"

#include "WarpComponent.h"
#include "WalkComponent.h"
#include "TargetMouseComponent.h"
#include "LockComponent.h"
#include "CapybaraAI.h"

#include <iostream>

using namespace Engine;

GameObject* ForgeCapybara(Engine::Scene* scene);

//Scene sceneObject;

int main(int argc, char* argv[])
{
	srand(static_cast <unsigned> (time(0)));


	//FreeConsole();
	App app = App();
	Engine::Scene* scene = app.CreateGame();

	// Prepares an OpenGL context so that we can send API calls
	app.Build();
	app.Load(scene);


	Shader::Load("assets/shaders/sprite.shader", "sprite");
	Shader::Load("assets/shaders/text.shader", "text");
	Shader::Load("assets/shaders/tile.shader", "tile");

	//Texture2D::Init();
	Texture2D::Load("assets/textures/Capybara.png", "capybara");
	Texture2D::Load("assets/textures/Shadow.png", "shadow");

	Font::Load("assets/fonts/arial.ttf", "arial");

	Texture2D::PrepareRenderer(Shader::Get("sprite"));
	Text::PrepareRenderer(Shader::Get("text"));



	scene->Load();

	// - Load Resources
	//Resources::LoadTexture("assets/textures/Capybara.png", true, "capybara");
	//Resources::LoadTexture("assets/textures/Shadow.png", true, "shadow");

	//Resources::LoadTilemap("assets/tilemaps/Pacman.tmx", "tilesheet");
	//Resources::LoadWav("assets/audio/Venus by SketchyLogic.wav", "venus");


	// - Create audio
	//GameObject* audi = scene->CreateGameObject();

	//AudioSourceComponent* audiComp = new AudioSourceComponent(audi);
	//audiComp->Attach(Resources::GetWav("beginning"));

	//audiComp->source->Play();
	//while (source->IsPlaying()) ;
	//cout << "No longer playing" << endl;

	// - CAPYBARA
	GameObject* capybara_GameObject = ForgeCapybara(scene);

	// Mainloop
	return app.Run(scene);
}



GameObject* ForgeCapybara(Engine::Scene* scene) {

	// - CAPYBARA SHADOW
	// The capybara shadow must be added BEFORE to be put behind in the rendering order

	GameObject* shadow_GameObject = scene->CreateGameObject();

	SpriteComponent* shadow_SpriteComponent = new SpriteComponent(shadow_GameObject);
	shadow_SpriteComponent
		->Set(Texture2D::Get("shadow"))
		->SetColour({ 0,0,0,128 });

	// - CAPYBARA

	GameObject* capybara_GameObject = scene->CreateGameObject();
	capybara_GameObject->position = Vector2(0);
	capybara_GameObject->scale = Vector2(4);

	SpriteComponent* capybara_SpriteComponent = new SpriteComponent(capybara_GameObject);
	capybara_SpriteComponent
		->Set(Texture2D::Get("capybara"))
		->AnimationSpeed(8)
		->SetColour({ 255,255,255 });

	WalkComponent* capybara_WalkComponent = new WalkComponent(capybara_GameObject);

	CapybaraAI* capybara_CapybaraAI = new CapybaraAI(capybara_GameObject);
	capybara_CapybaraAI->Bind(capybara_WalkComponent);


	// Tell the shadow to follow the capybara
	LockComponent* shadow_LockComponent = new LockComponent(shadow_GameObject);
	shadow_LockComponent->SetTarget(capybara_GameObject);


	return capybara_GameObject;
}