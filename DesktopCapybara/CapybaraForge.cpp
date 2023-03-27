#include "CapybaraForge.h"

#include "All.h"

#include "WalkComponent.h"
#include "CapybaraAI.h"
#include "LockComponent.h"

CapybaraForge::CapybaraForge(Engine::GameObject* gameObject, std::string name)
	: Component(gameObject, name)
{
}


void CapybaraForge::update(double time, double delta, Engine::Scene& game)
{
	Input input = Engine::App::instance->input;
	if (input.IsKey(GLFW_KEY_C) && input.IsKey(GLFW_KEY_A))
		ForgeCapybara();
}

//  +@@@@@-@@@@@@@==
//      +=@@@@@
//        @@%@@@
//       --     --
Engine::GameObject* CapybaraForge::ForgeCapybara()
{
	// - SHADOW
	// The capybara shadow must be added BEFORE to be put behind in the rendering order

	Engine::GameObject* shadow_GameObject = scene->CreateGameObject();

	auto shadow_SpriteComponent =
		shadow_GameObject->addComponent<SpriteComponent>()
		->setTexture2D(Texture2D::get("shadow"))
		->setColour({ 0,0,0,128 });
	shadow_SpriteComponent->size = 16;


	// - CAPYBARA

	Engine::GameObject* capybara_GameObject = scene->CreateGameObject()
		->SetPosition(0)
		->SetScale(rand() % 2 + 3);

	auto capybara_SpriteComponent =
		capybara_GameObject->addComponent<SpriteComponent>()
		->setTexture2D(Texture2D::get("capybara"));
	capybara_SpriteComponent->size = 16;
	capybara_SpriteComponent->crop = { rand() % 4, 0 };

	WalkComponent* capybara_WalkComponent = new WalkComponent(capybara_GameObject);

	// Animations
	//auto capybara_Animation = new AnimatedSprite<CapybaraStates, CapybaraActions>(capybara_GameObject, CapybaraStates::WANDER);
	//capybara_Animation->animation.AddTransition(AAAAAAA, TICK, WANDER);

	CapybaraAI* capybara_CapybaraAI = new CapybaraAI(capybara_GameObject);
	capybara_CapybaraAI->Bind(capybara_WalkComponent);

	// - HAT
	Engine::GameObject* hat_GameObject = scene->CreateGameObject();

	SpriteComponent* hat_SpriteComponent = new SpriteComponent(hat_GameObject);
	hat_SpriteComponent
		->setTexture2D(Texture2D::get("hat"));
	hat_SpriteComponent->size = 64;
	hat_SpriteComponent->crop = { rand() % 10,0 };

	//std::cout << hat_SpriteComponent->crop << std::endl;

	// Tell the gameobjects to follow the capybara

	auto shadow_LockComponent =
		shadow_GameObject->addComponent<LockComponent>()
		->SetTarget(capybara_GameObject)
		->LockPosition()->LockRotation()->LockScale()
		->LockSpriteReflection(capybara_SpriteComponent);

	auto hat_LockComponent =
		hat_GameObject->addComponent<LockComponent>()
		->SetTarget(capybara_GameObject)
		->LockPosition()->LockRotation()->LockScale()
		->LockSpriteReflection(capybara_SpriteComponent)
		->SetPositionOffset({ 0,-1 });

	return capybara_GameObject;
}