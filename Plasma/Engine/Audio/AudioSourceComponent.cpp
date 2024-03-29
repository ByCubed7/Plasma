// By @ByCubed7 on Twitter


//#define VERBOSE

#include "AudioSourceComponent.h"

#include "AudioScene.h"
#include "../Component.h"
#include "../GameObject.h"
#include "../Scene.h"
#include "../Components/SpriteComponent.h"

AudioSourceComponent::AudioSourceComponent(Engine::GameObject* gameObject, std::string name)
	: Component(gameObject, name)
{
	#ifdef VERBOSE
	cout << "AudioSourceComponent::Ctor" << endl;
	#endif
	source = gameObject->scene->audio->CreateSource();
	buffer = 0;
}

void AudioSourceComponent::update(double delta, Engine::Scene& game)
{
	//source->SetPosition(gameObject->position);
}

void AudioSourceComponent::Attach(Wav wavFile)
{
	buffer = gameObject->scene->audio->CreateBuffer(wavFile);
	source->bind(buffer->id);
}
