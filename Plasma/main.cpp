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
#include "FoodSpawner.h"

#include <iostream>
#include "Engine/Components/AnimatedSprite.h"

#include "Tests/VectorTest.h"

using namespace Engine;

GameObject* ForgeCapybara(Scene* scene);

int main(int argc, char* argv[])
{
	Tests::TestVector3();

	srand(static_cast <unsigned>(time(0)));

	//FreeConsole();
	App app = App();
	Scene* scene = app.CreateGame();

	// Prepares an OpenGL context so that we can send API calls
	app.Build();
	app.Load(scene);


	Shader::Load("Plasma/assets/shaders/sprite.shader", "sprite");
	Shader::Load("Plasma/assets/shaders/text.shader", "text");
	Shader::Load("Plasma/assets/shaders/tile.shader", "tile");

	//Texture2D::Init();
	Texture2D::Load("Plasma/assets/textures/Capybara.png", "capybara");
	Texture2D::Load("Plasma/assets/textures/Shadow.png", "shadow");
	Texture2D::Load("Plasma/assets/textures/Hat.png", "hat");
	Texture2D::Load("Plasma/assets/textures/Food.png", "food");

	Font::Load("Plasma/assets/fonts/arial.ttf", "arial");

	Texture2D::PrepareRenderer(Shader::Get("sprite"));
	Text::PrepareRenderer(Shader::Get("text"));

	scene->Load();

	//Resources::LoadTilemap("Plasma/assets/tilemaps/Pacman.tmx", "tilesheet");
	Resources::LoadWav("Plasma/assets/audio/Capybara.wav", "capybara");


	// - Create audio
	GameObject* audi = scene->CreateGameObject();

	AudioSourceComponent* audiComp = new AudioSourceComponent(audi);
	audiComp->Attach(Resources::GetWav("capybara"));

	audiComp->source->Play();
	//while (audiComp->source->IsPlaying()) ;
	//std::cout << "No longer playing" << std::endl;

	GameObject* controller_GameObject = scene->CreateGameObject()
		->SetPosition(0);

	controller_GameObject->Add<FoodSpawner>();


	// - CAPYBARA

	//for (int capycount = 0; capycount < 40; capycount++)
		GameObject* capybara = ForgeCapybara(scene);

	app.SetSize(app.GetWindow()->GetMonitorSize());

	// Mainloop
	return app.Run();
}


 
//  +@@@@@-@@@@@@@==
//      +=@@@@@
//        @@%@@@
//       --     --
GameObject* ForgeCapybara(Scene* scene) 
{
	// - SHADOW
	// The capybara shadow must be added BEFORE to be put behind in the rendering order

	GameObject* shadow_GameObject = scene->CreateGameObject();

	auto shadow_SpriteComponent =
		shadow_GameObject->Add<SpriteComponent>()
			->Set(Texture2D::Get("shadow"))
			->SetColour({ 0,0,0,128 });
	shadow_SpriteComponent->size = 16;


	// - CAPYBARA

	GameObject* capybara_GameObject = scene->CreateGameObject()
		->SetPosition(0)
		->SetScale(rand() % 2 + 3);

	auto capybara_SpriteComponent =
		capybara_GameObject->Add<SpriteComponent>()
			->Set(Texture2D::Get("capybara"));
	capybara_SpriteComponent->size = 16;
	capybara_SpriteComponent->crop = { rand() % 4, 0 };

	WalkComponent* capybara_WalkComponent = new WalkComponent(capybara_GameObject);

	// Animations
	//auto capybara_Animation = new AnimatedSprite<CapybaraStates, CapybaraActions>(capybara_GameObject, CapybaraStates::WANDER);
	//capybara_Animation->animation.AddTransition(AAAAAAA, TICK, WANDER);

	CapybaraAI* capybara_CapybaraAI = new CapybaraAI(capybara_GameObject);
	capybara_CapybaraAI->Bind(capybara_WalkComponent);

	// - HAT
	GameObject* hat_GameObject = scene->CreateGameObject();

	SpriteComponent* hat_SpriteComponent = new SpriteComponent(hat_GameObject);
	hat_SpriteComponent
		->Set(Texture2D::Get("hat"));
	hat_SpriteComponent->size = 64;
	hat_SpriteComponent->crop = { rand() % 10,0};

	//std::cout << hat_SpriteComponent->crop << std::endl;

	// Tell the gameobjects to follow the capybara

	auto shadow_LockComponent =
		shadow_GameObject->Add<LockComponent>()
			->SetTarget(capybara_GameObject)
			->LockPosition()->LockRotation()->LockScale()
			->LockSpriteReflection(capybara_SpriteComponent);

	auto hat_LockComponent = 
		hat_GameObject->Add<LockComponent>()
			->SetTarget(capybara_GameObject)
			->LockPosition()->LockRotation()->LockScale()
			->LockSpriteReflection(capybara_SpriteComponent)
			->SetPositionOffset({ 0,-1 });

	return capybara_GameObject;
}