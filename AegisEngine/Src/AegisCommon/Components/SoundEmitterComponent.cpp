#include "SoundEmitterComponent.h"
#include "SoundSystem.h"
#include "Entity.h"
#include "TransformComponent.h"

#define SoundSys SoundSystem::getInstance()

SoundEmitterComponent::SoundEmitterComponent(Entity* ent, std::string sound, std::string mode):
	AegisComponent("SoundEmitter", ent),soundName(sound)
{
	setDataAsInnerType(this);
	emitterData = SoundSys->createEmitter(ent->getTransform()->getPosition());
}

SoundEmitterComponent::~SoundEmitterComponent()
{
	SoundSys->removeEmitter(emitterData);
}

void SoundEmitterComponent::playSound()
{
	auto it = emitterData->channels.find(soundName);

	if (it != emitterData->channels.end())
		emitterData->channels[soundName]->channel = SoundSys->playSound(soundName);
	else
		emitterData->channels.insert({ soundName, SoundSys->createSoundChannel(SoundSys->playSound(soundName)) });
}

void SoundEmitterComponent::stop() 
{
	SoundSys->stopChannel(emitterData, soundName);
}

void SoundEmitterComponent::pause()
{
	SoundSys->pauseSound(emitterData, soundName);
}

void SoundEmitterComponent::resume()
{
	SoundSys->resumeSound(emitterData, soundName);
}

void SoundEmitterComponent::setVolume(float volume)
{
	SoundSys->setGeneralVolume(volume);
}

void SoundEmitterComponent::update(float deltaTime)
{
	SoundSys->updatePosition(emitterData, getEntity()->getTransform()->getPosition());
}

std::string SoundEmitterComponent::getSound() const
{
	return soundName;
}

void SoundEmitterComponent::setSound(std::string name)
{
	soundName = name;
}

inline SoundEmitterComponent* createSoundEmitter(Entity* ent, std::string sound, std::string mode) {
	return new SoundEmitterComponent(ent,sound,mode);
}

void SoundEmitterComponent::ConvertToLua(lua_State* state)
{
	getGlobalNamespace(state).
		beginNamespace("Aegis").
			beginNamespace("NativeComponents").
				addFunction("createSoundEmitter", createSoundEmitter).
				deriveClass<SoundEmitterComponent, AegisComponent>("SoundEmitter").
					addProperty("sound", &SoundEmitterComponent::getSound, &SoundEmitterComponent::setSound).
					addFunction("PlayClip", &SoundEmitterComponent::playSound).
					addFunction("StopClip", &SoundEmitterComponent::stop).
					addFunction("PauseClip", &SoundEmitterComponent::pause).
					addFunction("ResumeClip", &SoundEmitterComponent::resume).
					addFunction("SetVolume", &SoundEmitterComponent::setVolume).
				endClass().
			endNamespace().
		endNamespace();
}
