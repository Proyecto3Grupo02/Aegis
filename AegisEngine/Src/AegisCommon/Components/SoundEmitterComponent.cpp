#include "SoundEmitterComponent.h"
#include "SoundSystem.h"
#include "Entity.h"
#include "TransformComponent.h"

#define SoundSys SoundSystem::getInstance()

SoundEmitterComponent::SoundEmitterComponent(Entity* ent, std::string sound, std::string mode):
	AegisComponent("SoundEmitter", ent),soundName(sound)
{
	setDataAsInnerType(this);
	SoundSys->createEmitter(ent->getTransform()->getPosition());
}

SoundEmitterComponent::~SoundEmitterComponent()
{
}

void SoundEmitterComponent::playMusic()
{
	//emitterData->channels[soundName] = new SoundChannel(SoundSys->playMusic(soundName));
	//SoundSystem::getInstance()->playMusic(soundName);
}

void SoundEmitterComponent::playSound()
{
	//emitterData->channels[soundName] = new SoundChannel(SoundSystem::GetInstance()->playSound(soundName));
	SoundSystem::getInstance()->playSound(soundName);
}

void SoundEmitterComponent::stop(const std::string name) {

	auto it = emitterData->channels.find(name);
	if (it != emitterData->channels.end()) {
		it->second->channel->stop();
		delete it->second;
		emitterData->channels.erase(it);
	}
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
		addFunction("PlayMusic", &SoundEmitterComponent::playMusic).
		addFunction("PlaySound", &SoundEmitterComponent::playSound).
		addFunction("StopMusic", &SoundEmitterComponent::stop).
		
		endClass().
		endNamespace().
		endNamespace();
}
