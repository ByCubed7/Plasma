// By @ByCubed7 on Twitter

#pragma once

#include "../Component.h"

#include "Audio/AudioSource.h"
#include "Audio/AudioBuffer.h"
#include "Audio/Wav.h"

class AudioSourceComponent : public Component
{
public:
	AudioSourceComponent(GameObject* gameObject, std::string name = "AudioSourceComponent");

	void Update(double delta, Engine::Scene& game);

	void Attach(Wav wavFile);

	Audio::Source* source;

private:
	Audio::Buffer* buffer;
};