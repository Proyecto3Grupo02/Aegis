#include "SoundEmitterComponent.h"
#include "SoundSystem.h"

SoundEmitterComponent::SoundEmitterComponent(Entity* ent, std::string sound, std::string mode):
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
	//llama soundsystem.cpp->playSound y agrega la cancion a la lista
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
		addFunction("StopMusic", &SoundEmitterComponent::stopMusic).
		addFunction("StopSound", &SoundEmitterComponent::stopSound).
		
		endClass().
		endNamespace().
		endNamespace();
}
