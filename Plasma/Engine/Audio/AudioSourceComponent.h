// By @ByCubed7 on Twitter

#pragma once

#include "../Component.h"
#include "Wav.h"

namespace Audio {
	class Source;
	class Buffer;
}

class AudioSourceComponent : public Engine::Component
{
public:
	AudioSourceComponent(Engine::GameObject* gameObject, std::string name = "AudioSourceComponent");

	void Update(double delta, Engine::Scene& game);

	void Attach(Wav wavFile);

	Audio::Source* source;

private:
	Audio::Buffer* buffer;
};