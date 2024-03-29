// By @ByCubed7 on Twitter


//#define VERBOSE

#include "TextboxComponent.h"

#include "../GameObject.h"
#include "../Render/Renderers.h"

namespace UI {
	TextboxComponent::TextboxComponent(Engine::GameObject* gameObject, std::string name)
		: Component(gameObject, name)
	{}

	void TextboxComponent::draw(Render::Renderers& renderer)
	{
		renderer.text.draw(
			text,
			gameObject->position.x, gameObject->position.y,
			gameObject->scale.x,
			glm::vec2(0, 0),
			glm::vec3(0.3, 0.7f, 0.9f)
		);
	}
}