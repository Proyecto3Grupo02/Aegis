#include "SoundEmitterComponent.h"

SoundEmitterComponent::SoundEmitterComponent()
{
}

SoundEmitterComponent::~SoundEmitterComponent()
{
}

void SoundEmitterComponent::playSound(const std::string& soundname, bool reverb)
{
}

void SoundEmitterComponent::playMusic(const std::string& soundname, bool reverb)
{
}

void SoundEmitterComponent::stop(const std::string& sound)
{
}

void SoundEmitterComponent::pause(const std::string& sound)
{
}

void SoundEmitterComponent::resume(const std::string& sound)
{
}

void SoundEmitterComponent::setVolume(const std::string& sound)
{
}

void SoundEmitterComponent::setPitch(float pitch)
{
}

void SoundEmitterComponent::ConvertToLua(lua_State* state)
{
}
