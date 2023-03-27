// By @ByCubed7 on Twitter

#include "All.h"

#include <iostream>
#include "Engine/Components/AnimatedSprite.h"

#include "Tests/VectorTest.h"

#include "../DesktopCapybara/WarpComponent.h"
#include "../DesktopCapybara/WalkComponent.h"
#include "../DesktopCapybara/TargetMouseComponent.h"
#include "../DesktopCapybara/LockComponent.h"
#include "../DesktopCapybara/CapybaraAI.h"
#include "../DesktopCapybara/FoodSpawner.h"
#include "../DesktopCapybara/CapybaraForge.h"

using namespace Engine;

int main(int argc, char* argv[])
{
	srand(static_cast <unsigned>(time(0)));

	//FreeConsole();
	App app = App();
	Scene* scene = app.createScene();

	// Prepares an OpenGL context so that we can send API calls
	app.build();
	app.load(scene);

<<<<<<< Updated upstream

	Shader::Load("assets/shaders/sprite.shader", "sprite");
	Shader::Load("assets/shaders/text.shader", "text");
	Shader::Load("assets/shaders/tile.shader", "tile");

	//Texture2D::Init();
	Texture2D::Load("assets/textures/Capybara.png", "capybara");
	Texture2D::Load("assets/textures/Shadow.png", "shadow");
	Texture2D::Load("assets/textures/Hat.png", "hat");
	Texture2D::Load("assets/textures/Food.png", "food");

	Font::Load("assets/fonts/arial.ttf", "arial");

	Texture2D::PrepareRenderer(Shader::Get("sprite"));
	Text::PrepareRenderer(Shader::Get("text"));

	scene->Load();

	//Resources::LoadTilemap("assets/tilemaps/Pacman.tmx", "tilesheet");
	Wav::Load("assets/audio/Capybara.wav", "capybara");
=======
<<<<<<< Updated upstream
=======

	Shader::load("assets/shaders/sprite.shader", "sprite");
	Shader::load("assets/shaders/text.shader", "text");
	Shader::load("assets/shaders/tile.shader", "tile");

	//Texture2D::Init();
	Texture2D::load("assets/textures/Capybara.png", "capybara");
	Texture2D::load("assets/textures/Shadow.png", "shadow");
	Texture2D::load("assets/textures/Hat.png", "hat");
	Texture2D::load("assets/textures/Food.png", "food");

	Font::load("assets/fonts/arial.ttf", "arial");

	Texture2D::PrepareRenderer(Shader::get("sprite"));
	Text::PrepareRenderer(Shader::get("text"));

	scene->load();

	//Resources::LoadTilemap("assets/tilemaps/Pacman.tmx", "tilesheet");
	Wav::load("assets/audio/Capybara.wav", "capybara");
>>>>>>> Stashed changes

	// - Create audio
	GameObject* audi = scene->CreateGameObject();

	AudioSourceComponent* audiComp = new AudioSourceComponent(audi);
<<<<<<< Updated upstream
	audiComp->Attach(Wav::Get("capybara"));
=======
	audiComp->Attach(Wav::get("capybara"));
>>>>>>> Stashed changes

	audiComp->source->Play();
	//while (audiComp->source->IsPlaying()) ;
	//std::cout << "No longer playing" << std::endl;

	GameObject* controller_GameObject = scene->CreateGameObject()
		->SetPosition(0);

<<<<<<< Updated upstream
	controller_GameObject->Add<FoodSpawner>();

	CapybaraForge* forge = controller_GameObject->Add<CapybaraForge>();
	GameObject* capybara = forge->ForgeCapybara();


	app.SetSize(app.GetWindow()->GetMonitorSize());
=======
	controller_GameObject->addComponent<FoodSpawner>();

	CapybaraForge* forge = controller_GameObject->addComponent<CapybaraForge>();
	GameObject* capybara = forge->ForgeCapybara();


	//app.setSize(Vector2Int({ 700, 700 }));
	app.setSize(app.getMonitorSize());
>>>>>>> Stashed changes




	std::cout << "Close the console menu when you wish to quit~" << std::endl;
	std::cout << "Press C + A to add another capybara!!" << std::endl;


<<<<<<< Updated upstream
=======
>>>>>>> Stashed changes
>>>>>>> Stashed changes
	// Mainloop
	return app.run();
}


 
