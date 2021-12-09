// By @ByCubed7 on Twitter

//#define VERBOSE

#include "SpriteComponent.h"

#include "Component.h"
#include "Settings.h"
#include "AudioSourceComponent.h"

AudioSourceComponent::AudioSourceComponent(GameObject* gameObject, std::string name)
	: Component(gameObject, name)
{
	#ifdef VERBOSE
	cout << "AudioSourceComponent::Ctor" << endl;
	#endif
	source = gameObject->scene->audio->CreateSource();
	buffer = 0;
}

void AudioSourceComponent::Update(double delta, Engine::Scene& game)
{
	//source->SetPosition(gameObject->position);
}

void AudioSourceComponent::Attach(Wav wavFile)
{
	buffer = gameObject->scene->audio->CreateBuffer(wavFile);
	source->Bind(buffer->id);
}
