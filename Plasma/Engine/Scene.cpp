// By @ByCubed7 on Twitter

#include "Scene.h"

#include "Settings.h"
#include "Resources.h"
#include "SpriteRenderer.h"
#include "TextRenderer.h"
#include "Shader.h"
#include "Texture.h"
#include "GameObject.h"

#include "Component.h"
#include "BoxColliderComponent.h"

#include <glm/fwd.hpp>
#include "../Library/glad.h"
#include <GLFW/glfw3.h>

#include <typeinfo>
#include <algorithm>


Scene::Scene(GameConfig& setting)
{
	state = Scene::State::ACTIVE;
	input = Input();
	width = setting.screenWidth;
	height = setting.screenHeight;

	this->settings = setting;
}

Scene::~Scene()
{
	delete renderer;
}

GameObject* Scene::CreateGameObject()
{
	GameObject* newGameObject = new GameObject(this);
	gameObjects.emplace_back(newGameObject);
	return newGameObject;
}

void Scene::AddGameObject(GameObject* gameObject)
{
	gameObjects.emplace_back(gameObject);
}

void Scene::AddComponent(Component* component)
{
	components.emplace_back(component);
}

void Scene::Initialize()
{
	// As this is 2D we don't have to worry about perspective, use orthographic projection
	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->width), static_cast<float>(this->height), 0.0f, -1.0f, 1.0f);

	// - Load and Config shaders
	Resources::LoadShader("assets/shaders/sprite.vs", "assets/shaders/sprite.frag", nullptr, "sprite");
	Resources::LoadShader("assets/shaders/text.vs", "assets/shaders/text.frag", nullptr, "text");
	Resources::LoadShader("assets/shaders/tile.vs", "assets/shaders/tile.frag", nullptr, "tile");

	// Sprite
	Shader ShaderSprite = Resources::GetShader("sprite");
	ShaderSprite.Use().SetInteger("image", 0);
	ShaderSprite.SetMatrix4("projection", projection);
	ShaderSprite.SetInteger("index", 1);

	// Text
	Shader ShaderText = Resources::GetShader("text");
	ShaderText.Use().SetInteger("text", 0);
	ShaderText.SetMatrix4("projection", projection);

	//* Tilemap
	Shader ShaderTile = Resources::GetShader("tile");
	ShaderTile.Use().SetInteger("image", 0);
	ShaderTile.SetMatrix4("projection", projection);
	ShaderTile.SetInteger("index", 1);
	//*/


	// Load Renderer
	renderer = new Render::Renderers(
		ShaderSprite,
		ShaderText,
		ShaderTile
	);

	// - Load Text Fonts
	Resources::LoadFont("assets/fonts/arial.ttf", "arial");
}

void Scene::ProcessInput(double dt)
{
	// If the escape key is pressed, set the game to closing
	if (input.IsKey(input.Key_Escape))
		state = State::CLOSING;
	
	if (input.IsKeyDown(input.Key_P))
		state = state == State::ACTIVE ? State::PAUSED : State::ACTIVE;

	//std::cout << input.IsKeyDown(input.Key_P);

	input.Tick();
}

void Scene::Update(double delta) 
{
	// - IF PAUSED, DO NOTHING!
	if (state != State::ACTIVE) return;

	// Update all of the components
	for (const auto& component : components)
	{
		component->Update(delta, *this);
	}


	// - Update all of the colliders

	//*/ First, put all of them on axis
	vector<tuple<int, bool, BoxColliderComponent*>> axis = {};
	for (const auto& collider : colliders)
	{
		BoxColliderComponent box = *collider;
		axis.push_back({
			collider->bounds.lowerBound.x,
			false,
			collider
		});
		axis.push_back({
			collider->bounds.upperBound.x,
			true,
			collider
		});
	}

	sort(axis.begin(), axis.end(), [](auto a, auto b) { return get<0>(a) > get<0>(b); });

	map<BoxColliderComponent*, BoxColliderComponent*> collidersToCheck = {};
	
	list<BoxColliderComponent*> inRange = {};
	for (const auto& axi : axis)
	{
		// bool, BoxColliderComponent

		BoxColliderComponent* currentCollider = get<2>(axi);

		if (get<1>(axi))
		{
			// Check if any are colliding
			for (const auto& colliderInRange : inRange)
				collidersToCheck[currentCollider] = colliderInRange;

			inRange.push_back(currentCollider);
		}
		else inRange.remove(currentCollider);
	}
	//*/

	for (auto const& current : collidersToCheck)
	{
		BoxColliderComponent* currentCollider = current.first;
		BoxColliderComponent* collidingCollider = current.second;

		bool colliding = currentCollider->GetBounds().Overlaps(collidingCollider->GetBounds());

		// Calculate whether the the collider was already colliding from the frame before
		auto it = collidersColliding.find(currentCollider);
		bool isAlreadyColliding = it != collidersColliding.end() && it->second == collidingCollider;

		if (colliding)
		{
			if (isAlreadyColliding)
				currentCollider->OnCollisionStay();
			else {
				currentCollider->OnCollisionEnter();
				collidersColliding[currentCollider] = collidingCollider;
			}
		}
		else
		{
			if (isAlreadyColliding)
			{
				currentCollider->OnCollisionExit();
				collidersColliding.erase(currentCollider);
			}
		}
	}


}

void Scene::Render()
{
	//Renderer->DrawSprite(Resources::GetTexture("Player"),
	//    glm::vec2(300.0f, 300.0f), glm::vec2(400.0f, 400.0f), 75.0f, glm::vec3(0.5f, 0.5f, 0.0f));

	/*
	for (std::unique_ptr<GameObject>& gameObject : gameObjects)
	{
		gameObject->Draw(*renderer);
	}
	//*/

	for (const auto& component : components)
	{
		component->Draw(*renderer);
		//cout << "Drawing: " << component->ToString() << endl;
		//cout << "Drawing: " << component->gameObject->position.x << "," << component->gameObject->position.y << endl;
		//cout << "Game::GRender.Renderer:" << renderer << " Object:" << typeid(*component).name() << endl;
	}

}
