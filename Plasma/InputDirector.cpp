// By @ByCubed7 on Twitter

#include "All.h"

#include "InputDirector.h"

InputDirector::InputDirector(GameObject* gameObject, std::string name)
	: Component(gameObject, name)
{
	controller = nullptr;
}

InputDirector* InputDirector::SetController(TileLockedController* newController)
{
	controller = newController;
	return this;
}

void InputDirector::PassInputDirection()
{
	controller->SetInputDirection(inputDirection);
}
