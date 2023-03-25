#include "FoodSpawner.h"
#include "LockComponent.h"


FoodSpawner::FoodSpawner(Engine::GameObject* gameObject, std::string name) :
	Component(gameObject, name)
{
}

inline Engine::GameObject* createFood(Engine::Scene* scene) 
{	
	auto shadow_GameObject = scene->CreateGameObject();
	auto shadow_SpriteComponent =
		shadow_GameObject->Add<SpriteComponent>()
		->Set(Texture2D::Get("shadow"))
		->SetColour({ 0,0,0,128 });
	shadow_SpriteComponent->size = 16;



	auto newFood = scene->CreateGameObject();
	newFood->position = 100;
	newFood->scale = 3;

	auto newFood_SpriteComponent = newFood
		->Add<SpriteComponent>()
		->Set(Texture2D::Get("food"));

	newFood_SpriteComponent->size = 32;
	newFood_SpriteComponent->crop = 0;


	auto shadow_LockComponent =
		shadow_GameObject->Add<LockComponent>()
		->SetTarget(newFood)
		->LockPosition()->LockRotation()->LockScale()
		->LockSpriteReflection(newFood_SpriteComponent);

	return newFood;
}

void FoodSpawner::Update(double time, double delta, Engine::Scene& game)
{
	if (false) {
	//if (Engine::App::instance->input.IsKeyDown(Input::Key_A)) {
		//std::cout << "AAAAAAA" << std::endl;
		createFood(scene);
	}
}



