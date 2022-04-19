#include "SoundEmitterComponent.h"

SoundEmitterComponent::SoundEmitterComponent(Entity* ent, std::string sound):
	AegisComponent("SoundEmmiter", ent), mSound_(sound)
{
	mEmmiter_ = new SoundEmitter();
}

SoundEmitterComponent::~SoundEmitterComponent()
{
	delete mEmmiter_;
}

void SoundEmitterComponent::playSound(const std::string& soundname, bool reverb)
{
	mEmmiter_->playSound(soundname, reverb);
}

void SoundEmitterComponent::playMusic(const std::string& soundname, bool reverb)
{
	mEmmiter_->playMusic(mSound_, reverb);
}

std::string SoundEmitterComponent::getSound() const
{
	return mSound_;
}

void SoundEmitterComponent::setSound(std::string sound)
{
	mSound_ = sound;
}

void SoundEmitterComponent::stop()
{
	mEmmiter_->stop(mSound_);
}

void SoundEmitterComponent::pause()
{
	mEmmiter_->pause(mSound_);
}

void SoundEmitterComponent::resume()
{
	mEmmiter_->resume(mSound_);
}

void SoundEmitterComponent::setVolume(float vol)
{
	mEmmiter_->setVolume(vol);
}

void SoundEmitterComponent::setPitch(float pitch)
{
	mEmmiter_->setPitch(pitch);
}

SoundEmitterComponent* createSoundEmitter(Entity* ent, std::string sound) {

	return new SoundEmitterComponent(ent, sound);
}

void SoundEmitterComponent::ConvertToLua(lua_State* state)
{
	getGlobalNamespace(state).
		beginNamespace("Aegis").
		beginNamespace("NativeComponents").
		addFunction("createSoundEmitter", createSoundEmitter).
		deriveClass<SoundEmitterComponent, AegisComponent>("SoundEmmiter").
		addProperty("sound", &SoundEmitterComponent::getSound, &SoundEmitterComponent::setSound).
		endClass().
		endNamespace().
		endNamespace();
}