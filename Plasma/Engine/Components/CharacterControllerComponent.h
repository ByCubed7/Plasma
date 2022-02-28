// By @ByCubed7 on Twitter

#pragma once

#include "../AABB.h"
#include "../Vector2.h"
#include "../Component.h"
#include "../GameObject.h"
#include "../Scene.h"
#include "../Event.h"
#include "../Dispatcher.h"
#include "../Render/Renderers.h"
#include "../Render/Texture2D.h"

class GameObject;
namespace Engine { class Scene; }
namespace Render { struct Renderers; }

class CharacterControllerComponent : public Engine::Component
{
public:
	CharacterControllerComponent(Engine::GameObject* gameObject, std::string name = "CharacterControllerComponent");
	void Update(double delta, Engine::Scene& game) override;
};

