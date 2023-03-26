// By @ByCubed7 on Twitter

//#define VERBOSE

#include "Scene.h"

#include "Render/Shader.h"
#include "Render/Renderers.h"
#include "Components/BoxColliderComponent.h"
#include "Audio/AudioScene.h"

#include "Window.h"
#include "GameObject.h"
#include "Component.h"
#include "Input.h"
#include "App.h"

#include "OpenGL.h"

#include <typeinfo>
#include <algorithm>

namespace Engine 
{
	Scene::Scene(App* app)
	{
		this->app = app;

		state = Scene::State::ACTIVE;

		audio = new Audio::Scene();
	}

	Scene::~Scene()
	{
		delete audio;
		delete renderer;
	}

	Window* Scene::getWindow()
	{
		return app->getWindow();
	}

	GameObject* Scene::CreateGameObject()
	{
		GameObject* newGameObject = new GameObject(this);
		AddGameObject(newGameObject);
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

	void Scene::load()
	{
		Vector2Int size = app->getSize();
		glm::mat4 projection = glm::ortho(0.0f, (float)size.x, (float)size.y, 0.0f, -1.0f, 1.0f);
		
		// - Config shaders

		Shader ShaderSprite = Shader::getGLFW("sprite");
		ShaderSprite.Use()
			.SetInteger("image", 0)
			.SetInteger("index", 1)
			.SetMatrix4("projection", projection);

		// Text
		Shader ShaderText = Shader::getGLFW("text");
		ShaderText.Use()
			.SetInteger("text", 0)
			.SetMatrix4("projection", projection);
		
		//* Tilemap
		Shader ShaderTile = Shader::getGLFW("tile");
		ShaderTile.Use()
			.SetInteger("image", 0)
			.SetInteger("index", 1)
			.SetMatrix4("projection", projection);

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
		// As this is 2D we don't have to worry about perspective, use orthographic projection
		Vector2Int size = app->getSize();
		glm::mat4 projection = glm::ortho(0.0f, (float)size.x, (float)size.y, 0.0f, -1.0f, 1.0f);

		Shader::getGLFW("sprite").Use().SetMatrix4("projection", projection);
		Shader::getGLFW("text").Use().SetMatrix4("projection", projection);
		Shader::getGLFW("tile").Use().SetMatrix4("projection", projection);
	}

	void Scene::ProcessInput()
	{
		// Get mouse position
		double xpos, ypos;
		glfwGetCursorPos(app->getWindow()->getGLFW(), &xpos, &ypos);
		app->input.SetMousePosition(xpos, ypos);

		// If the escape key is pressed, set the game to closing
		if (app->input.IsKey(Input::Key_Escape))
			state = State::CLOSING;
	
		if (app->input.IsKeyDown(Input::Key_P))
			state = state == State::ACTIVE ? State::PAUSED : State::ACTIVE;

		//std::cout << input.IsKeyDown(input.Key_P);
	}

	void Scene::update(double time, double delta)
	{
		// - IF PAUSED, DO NOTHING!
		if (state != State::ACTIVE) return;

		// Update all of the components
		for (const auto& component : components)
		{
			component->update(time, delta, *this);
		}

		// We don't currently use colliders
		return;

		// - Update all of the colliders

		//*/ First, put all of them on axis
		std::vector<std::tuple<Vector2, bool, BoxColliderComponent*>> axis = {};
		for (const auto& collider : colliders)
		{
			BoxColliderComponent box = *collider;

			AABB bounds = collider->getBounds();

			axis.push_back({
				bounds.min,
				false,
				collider
			});
			axis.push_back({
				bounds.max,
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

			bool colliding = AABB::overlaps(currentCollider->getBounds(), collidingCollider->getBounds());

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
			component->draw(*renderer);
			//std::cout << "Drawing: " << component->ToString() << std::endl;
			//std::cout << "Drawing: " << component->gameObject->position.x << "," << component->gameObject->position.y << std::endl;
			//cout << "Game::GRender.Renderer:" << renderer << " Object:" << typeid(*component).name() << endl;
		}

	}
}