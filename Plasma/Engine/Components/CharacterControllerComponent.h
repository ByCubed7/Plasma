// By @ByCubed7 on Twitter

#pragma once

#include "../Component.h"
#include <string>

namespace Engine { class Scene; class GameObject;  }
namespace Render { struct Renderers; }

class CharacterControllerComponent : public Engine::Component
{
public:
	CharacterControllerComponent(Engine::GameObject* gameObject, std::string name = "CharacterControllerComponent");
	void update(double time, double delta, Engine::Scene& game) override;
};

