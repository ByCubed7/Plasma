// By @ByCubed7 on Twitter

#include "TextboxComponent.h"

namespace UI {
	TextboxComponent::TextboxComponent(GameObject* gameObject, std::string name)
		: Component(gameObject, name)
	{}

	void TextboxComponent::Draw(Render::Renderers& renderer)
	{
		renderer.text.RenderText(
			text,
			gameObject->position.x, gameObject->position.y,
			gameObject->scale.x,
			glm::vec2(0, 0),
			glm::vec3(0.3, 0.7f, 0.9f)
		);
	}
}