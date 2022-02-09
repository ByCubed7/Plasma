// By @ByCubed7 on Twitter

#include "All.h"
//#define VERBOSE

#include "AudioSourceComponent.h"

#include "../Component.h"
#include "../GameObject.h"
#include "../Settings.h"
#include "../Components/SpriteComponent.h"

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
