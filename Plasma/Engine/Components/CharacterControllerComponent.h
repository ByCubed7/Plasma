// By @ByCubed7 on Twitter

#pragma once

#include "../Engine/AABB.h"
#include "../Engine/Vector2.h"
#include "../Engine/Component.h"
#include "../Engine/GameObject.h"
#include "../Engine/Scene.h"
#include "../Engine/Event.h"
#include "../Engine/Dispatcher.h"
#include "../Render/Renderers.h"
#include "../Render/Texture2D.h"

class GameObject;
namespace Engine { class Scene; }
namespace Render { class Renderers; }

class CharacterControllerComponent : public Component
{
public:
	CharacterControllerComponent(GameObject* gameObject, std::string name = "CharacterControllerComponent");
	void Update(double delta, Engine::Scene& game) override;
};

