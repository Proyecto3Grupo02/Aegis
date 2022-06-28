#include "SoundEmitterComponent.h"
#include "SoundSystem.h"
#include "Entity.h"
#include "TransformComponent.h"

#define SoundSys SoundSystem::getInstance()
#define LuaSys LuaManager::getInstance()

SoundEmitterComponent::SoundEmitterComponent(Entity* ent, SoundEmitterComponentData data):
	AegisComponent("SoundEmitter", ent),soundEmitterData(data)
{
	setDataAsInnerType(this);
	emitterData = SoundSys->createEmitter(ent->getTransform()->getPosition());
}

SoundEmitterComponent::~SoundEmitterComponent()
{
	SoundSys->removeEmitter(emitterData);
}

void SoundEmitterComponent::init()
{
	AegisComponent::init();

	if (soundEmitterData.playOnInit)
		playSound();
}

void SoundEmitterComponent::playSound()
{
	auto it = emitterData->channels.find(soundEmitterData.sound);

	if (it != emitterData->channels.end())
		(*it).second->channel = SoundSys->playSound(soundEmitterData.sound, soundEmitterData.channelName);
	else
		emitterData->channels.insert({ soundEmitterData.sound, SoundSys->createSoundChannel(SoundSys->playSound(soundEmitterData.sound, soundEmitterData.channelName)) });

	setChannelProperties(emitterData->channels.at(soundEmitterData.sound)->channel);
}

void SoundEmitterComponent::stop() 
{
	SoundSys->stopChannel(emitterData, soundEmitterData.sound);
}

void SoundEmitterComponent::pause()
{
	SoundSys->pauseSound(emitterData, soundEmitterData.sound);
}

void SoundEmitterComponent::resume()
{
	SoundSys->resumeSound(emitterData, soundEmitterData.sound);
}

float SoundEmitterComponent::getVolume() const
{
	float volume = 0;
	auto it = emitterData->channels.find(soundEmitterData.sound);
	if (it != emitterData->channels.end())
		(*it).second->channel->getVolume(&volume);
	return volume;
}

void SoundEmitterComponent::setVolume(float volume)
{
	auto it = emitterData->channels.find(soundEmitterData.sound);

	if (it != emitterData->channels.end())
		(*it).second->channel->setVolume(volume);
}

float SoundEmitterComponent::getPitch() const
{
	return soundEmitterData.pitch;
}

void SoundEmitterComponent::setPitch(float pitch)
{
	auto it = emitterData->channels.find(soundEmitterData.sound);

	if (it != emitterData->channels.end())
		(*it).second->channel->setPitch(pitch);
	soundEmitterData.pitch = pitch;
}

void SoundEmitterComponent::setChannelProperties(Channel* channel)
{
	channel->setVolume(soundEmitterData.volume);
	channel->setPitch(soundEmitterData.pitch);

	channel->setMode(soundEmitterData.loopCount != 0 ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF);
	channel->setLoopCount(soundEmitterData.loopCount);

	if (soundEmitterData.minMax3DDistance.x != 0 || soundEmitterData.minMax3DDistance.y != 0)
	{
		channel->set3DMinMaxDistance(soundEmitterData.minMax3DDistance.x, soundEmitterData.minMax3DDistance.y);
		channel->setMode(FMOD_3D);
	}
	else 
		channel->setMode(FMOD_2D);
}

void SoundEmitterComponent::update(float deltaTime)
{
	SoundSys->updatePosition(emitterData, getEntity()->getTransform()->getPosition());
}

int SoundEmitterComponent::getLoopCount() const
{
	return soundEmitterData.loopCount;
}

void SoundEmitterComponent::setLoopCount(int loopCount)
{
	soundEmitterData.loopCount = loopCount;
}

std::string SoundEmitterComponent::getSound() const
{
	return soundEmitterData.sound;
}

void SoundEmitterComponent::setSound(std::string name)
{
	soundEmitterData.sound = name;
}

std::string SoundEmitterComponent::getChannelName() const
{
	return soundEmitterData.channelName;
}

void SoundEmitterComponent::setChannelName(const std::string& name)
{
	soundEmitterData.channelName = name;
}

inline SoundEmitterComponent* createSoundEmitter(Entity* ent, luabridge::LuaRef args) {
	SoundEmitterComponent::SoundEmitterComponentData data
	{
		LuaSys->parseString(args["sound"], ""),
		LuaSys->parseString(args["channel"], "default"),
		{0,0},
		LuaSys->parseFloat(args["volume"], 1),
		LuaSys->parseFloat(args["loopCount"], 0),
		LuaSys->parseFloat(args["pìtch"], 1),
		LuaSys->parseBool(args["playOnInit"], false)
	};
	
	if(!args["minMax3DDistance"].isNil())
	{
		data.minMax3DDistance.x = LuaSys->parseFloat(args["minMax3DDistance"]["min"], 0);
		data.minMax3DDistance.y = LuaSys->parseFloat(args["minMax3DDistance"]["max"], 0);
	}

	return new SoundEmitterComponent(ent, data);
}

void SoundEmitterComponent::ConvertToLua(lua_State* state)
{
	getGlobalNamespace(state).
		beginNamespace("Aegis").
			beginNamespace("NativeComponents").
				addFunction("CreateSoundEmitter", createSoundEmitter).
				deriveClass<SoundEmitterComponent, AegisComponent>("SoundEmitter").
					addProperty("sound", &SoundEmitterComponent::getSound, &SoundEmitterComponent::setSound).
					addProperty("loopCount", &SoundEmitterComponent::getLoopCount, &SoundEmitterComponent::setLoopCount).
					addProperty("volume", &SoundEmitterComponent::getVolume, &SoundEmitterComponent::setVolume).
					addProperty("pitch", &SoundEmitterComponent::getPitch, &SoundEmitterComponent::setPitch).
					addProperty("channel", &SoundEmitterComponent::getChannelName, &SoundEmitterComponent::setChannelName).
					addFunction("PlayClip", &SoundEmitterComponent::playSound).
					addFunction("StopClip", &SoundEmitterComponent::stop).
					addFunction("PauseClip", &SoundEmitterComponent::pause).
					addFunction("ResumeClip", &SoundEmitterComponent::resume).
				endClass().
			endNamespace().
		endNamespace();
}