// By @ByCubed7 on Twitter

#include "All.h"
//#define VERBOSE

#include "Scene.h"

#include "Window.h"
#include "Resources.h"
#include "GameObject.h"
#include "Component.h"
#include "Input.h"
#include "Render/Shader.h"
#include "Components/BoxColliderComponent.h"

#include <typeinfo>
#include <algorithm>

namespace Engine 
{

	Scene::Scene(App* app)
	{
		this->app = app;

		state = Scene::State::ACTIVE;
		input = Input();

		audio = new Audio::Scene();
	}

	Scene::~Scene()
	{
		delete audio;
		delete renderer;
	}

	Window* Scene::GetWindow()
	{
		return app->GetWindow();
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

	void Scene::Load() 
	{
		Vector2 size = app->GetSize();
		glm::mat4 projection = glm::ortho(0.0f, size.x, size.y, 0.0f, -1.0f, 1.0f);
		
		// - Load and Config shaders

		// Sprite
		Shader ShaderSprite = Resources::LoadShader("assets/shaders/sprite.vs", "assets/shaders/sprite.frag", nullptr, "sprite");
		ShaderSprite.Use();
		ShaderSprite.SetInteger("image", 0);
		ShaderSprite.SetInteger("index", 1);
		ShaderSprite.SetMatrix4("projection", projection);

		// Text
		Shader ShaderText = Resources::LoadShader("assets/shaders/text.vs", "assets/shaders/text.frag", nullptr, "text");
		ShaderText.Use();
		ShaderText.SetInteger("text", 0);
		ShaderText.SetMatrix4("projection", projection);
		
		//* Tilemap
		Shader ShaderTile = Resources::LoadShader("assets/shaders/tile.vs", "assets/shaders/tile.frag", nullptr, "tile");
		ShaderTile.Use();
		ShaderTile.SetInteger("image", 0);
		ShaderTile.SetInteger("index", 1);
		ShaderTile.SetMatrix4("projection", projection);

		// - Load Text Fonts
		Resources::LoadFont("assets/fonts/arial.ttf", "arial");

		// Load Renderer
		renderer = new Render::Renderers(
			ShaderSprite,
			ShaderText,
			ShaderTile
		);

		// - Load Audio
		audio->Prepare();
	}

	void Scene::UpdateProjection()
	{
		return;
		// As this is 2D we don't have to worry about perspective, use orthographic projection
		Vector2 size = app->GetSize();
		glm::mat4 projection = glm::ortho(0.0f, (float)size.x, (float)size.y, 0.0f, -1.0f, 1.0f);

		Resources::GetShader("sprite").Use().SetMatrix4("projection", projection);
		Resources::GetShader("text").Use().SetMatrix4("projection", projection);
		Resources::GetShader("tile").Use().SetMatrix4("projection", projection);		
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
		std::vector<std::tuple<Vector2, bool, BoxColliderComponent*>> axis = {};
		for (const auto& collider : colliders)
		{
			BoxColliderComponent box = *collider;
			axis.push_back({
				collider->GetBounds().lowerBound,
				false,
				collider
			});
			axis.push_back({
				collider->GetBounds().upperBound,
				true,
				collider
			});
		}

		std::sort(axis.begin(), axis.end(), [](std::tuple<Vector2, bool, BoxColliderComponent*> a, std::tuple<Vector2, bool, BoxColliderComponent*> b) {
			//std::get<0>(a) > 
			if (std::get<0>(a).x < std::get<0>(b).x) return true;
			if (std::get<0>(a).x == std::get<0>(b).x && std::get<0>(a).y < std::get<0>(b).y) return true;
			return false;
		});

		std::map<BoxColliderComponent*, BoxColliderComponent*> collidersToCheck = {};
	
		std::list<BoxColliderComponent*> inRange = {};
		for (const auto& axi : axis)
		{
			// bool, BoxColliderComponent

			BoxColliderComponent* currentCollider = std::get<2>(axi);

			if (std::get<1>(axi))
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
				if (isAlreadyColliding) {
					currentCollider->OnCollisionStay();
					//std::cout << "Collidering! " << currentCollider->gameObject->position.ToString() << std::endl;
				}
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
}