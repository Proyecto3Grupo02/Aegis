#include "SoundEmitterComponent.h"
#include "SoundSystem.h"

SoundEmitterComponent::SoundEmitterComponent(Entity* ent, std::string sound):
	AegisComponent("SoundEmitter", ent),soundName(sound)
{
	setDataAsInnerType(this);
}

SoundEmitterComponent::~SoundEmitterComponent()
{
}

void SoundEmitterComponent::playMusic()
{
	SoundSystem::getInstance()->playMusic(soundName);
}

void SoundEmitterComponent::playSound()
{
	SoundSystem::getInstance()->playSound(soundName);
}

void SoundEmitterComponent::stopMusic()
{
	SoundSystem::getInstance()->stopMusic(soundName);
}

void SoundEmitterComponent::stopSound()
{
	SoundSystem::getInstance()->stopSound(soundName);
}

std::string SoundEmitterComponent::getSound() const
{
	return soundName;
}

void SoundEmitterComponent::setSound(std::string name)
{
	soundName = name;
}

inline SoundEmitterComponent* createSoundEmitter(Entity* ent, std::string sound) {
	return new SoundEmitterComponent(ent,sound);
}

void SoundEmitterComponent::ConvertToLua(lua_State* state)
{
	getGlobalNamespace(state).
		beginNamespace("Aegis").
		beginNamespace("NativeComponents").
		addFunction("createSoundEmitter", createSoundEmitter).
		deriveClass<SoundEmitterComponent, AegisComponent>("SoundEmitter").
		addProperty("sound", &SoundEmitterComponent::getSound, &SoundEmitterComponent::setSound).
		endClass().
		endNamespace().
		endNamespace();
}
