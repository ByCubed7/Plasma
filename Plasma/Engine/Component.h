// By @ByCubed7 on Twitter

#pragma once

#include "Object.h"

// Forward Declaration
namespace Render { struct Renderers; }

namespace Engine {

	// Forward Declaration
	class Scene;
	class GameObject;

	class Component : public Object
	{
	public:
		Component(GameObject* gameObject, std::string name = "Component");

		GameObject* gameObject;
		Engine::Scene* scene;

		virtual void update(double time, double delta, Engine::Scene& game);
		virtual void draw(Render::Renderers& renderer);
	};
}