// By @ByCubed7 on Twitter

#include "All.h"

#include "GhostStateComponent.h"

GhostStateComponent::GhostStateComponent(GameObject* gameObject, std::string name)
	: Component(gameObject, name)
{
	state = GhostState::CHASING;
}

void GhostStateComponent::Chase()		{ state = GhostState::CHASING; }
void GhostStateComponent::Scatter()		{ state = GhostState::SCATTERING; }
void GhostStateComponent::Frighten()	{ state = GhostState::FRIGHTENED; }
void GhostStateComponent::Kill()		{ state = GhostState::DEAD; }

bool GhostStateComponent::IsChasing()		{ return state == GhostState::CHASING; }
bool GhostStateComponent::IsScattered()		{ return state == GhostState::SCATTERING; }
bool GhostStateComponent::IsFrightened()	{ return state == GhostState::FRIGHTENED; }
bool GhostStateComponent::IsDead()			{ return state == GhostState::DEAD; }

