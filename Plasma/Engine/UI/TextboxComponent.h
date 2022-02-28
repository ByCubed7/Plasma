// By @ByCubed7 on Twitter

#pragma once

#include "../Component.h"

#include "../Event.h"
#include "../Dispatcher.h"

namespace UI {
	class TextboxComponent : public Engine::Component
	{
	public:
		//struct NameEvent;

		TextboxComponent(Engine::GameObject* gameObject, std::string name = "TextboxComponent");

		std::string text;

		//void Update(double delta, Engine::Scene& game) override;
		void Draw(Render::Renderers& renderer) override;


		//void NameEvent();

		// Event Dispatchers
		//Dispatcher<NameEventParams> nameEvent;
	};

	//struct TextboxComponent::NameEventParams
	//{
	//	NameEventParams(TextboxComponent* parent);
	//	NameEventParams* collider;
	//
	//	operator int() const { return (int)collider->gameObject->position.x; }
	//};
}