#include "SoundSystem.h"

#include <fmod_errors.h>
//#include "DebugUtils.h"

SoundSystem::SoundSystem() : system(nullptr), listener(nullptr), music(nullptr), soundEffects(nullptr)
{
}

SoundSystem::~SoundSystem()
{
}

void SoundSystem::init()
{
	generalVolume = 1;
	musicVolume = 1;
	soundVolume = 1;
	FMOD_RESULT result = FMOD::System_Create(&system);
	ERRCHECK(result);

	result = system->init(128, FMOD_INIT_NORMAL, 0);
	ERRCHECK(result);

	result = system->createChannelGroup("music", &music);
	ERRCHECK(result);

	FMOD::ChannelGroup* master;
	result = system->getMasterChannelGroup(&master);
	ERRCHECK(result);

	result = master->addGroup(music);
	ERRCHECK(result);

	result = system->createChannelGroup("soundEffect", &soundEffects);
	ERRCHECK(result);

	result = master->addGroup(soundEffects);
	ERRCHECK(result);

	LOG("SOUND SYSTEM: System started");
}

void SoundSystem::close()
{
	for (EmitterData* emitter : emitters)
		removeEmitter(emitter);

	removeListener();

	system->close();
	system->release();

	destroy();
}


Sound* SoundSystem::createSound(const std::string& name, const SoundMode& mode)
{
	Sound* sound;
	if (system->createSound(name.c_str(), mode, nullptr, &sound) == FMOD_RESULT::FMOD_OK)
		return sound;
	return nullptr;
}

FMOD::Channel* SoundSystem::playSound(const std::string& name)
{
	Channel* channel;
	Sound* sound = getSound(name);
	if (sound == nullptr) return nullptr;

	FMOD_RESULT result = system->playSound(sound, soundEffects, false, &channel);
	ERRCHECK(result);
	channel->set3DMinMaxDistance(50, 10000);
	return channel;
}

FMOD::Channel* SoundSystem::playMusic(const std::string& name)
{
	Channel* channel;
	Sound* sound = getSound(name);
	if (sound == nullptr) return nullptr;

	FMOD_RESULT result = system->playSound(sound, music, false, &channel);
	ERRCHECK(result);
	channel->set3DMinMaxDistance(50, 10000);
	return channel;
}

void SoundSystem::setPauseAllSounds(bool pause)
{
	ChannelGroup* master;

	FMOD_RESULT result = system->getMasterChannelGroup(&master);
	
	ERRCHECK(result);

	master->setPaused(pause);
}

void SoundSystem::setMusicVolume(float volume)
{
	music->setVolume(volume);
	musicVolume = volume;
}

void SoundSystem::setSoundEffectsVolume(float volume)
{
	soundEffects->setVolume(volume);
	soundVolume = volume;
}

void SoundSystem::setGeneralVolume(float volume)
{
	ChannelGroup* master;
	FMOD_RESULT result = system->getMasterChannelGroup(&master);

	ERRCHECK(result);

	master->setVolume(volume);
	generalVolume = volume;
}

void SoundSystem::setListenerAttributes(const Vector3& position, const Vector3& forward, const Vector3& up)
{
	FMOD_VECTOR pos, vel, forwardTmp, upTmp;
	pos = { float(position.x) ,float(position.y) ,float(position.z) };
	vel = { 0,0,0 };
	forwardTmp = { float(forward.x) ,float(forward.y) ,float(forward.z) };
	upTmp = { float(up.x) ,float(up.y) ,float(up.z) };
	system->set3DListenerAttributes(0, &pos, &vel, &forwardTmp, &upTmp);
}

float SoundSystem::getGeneralVolume() const
{
	return generalVolume;
}

float SoundSystem::getMusicVolume() const
{
	return musicVolume;
}

float SoundSystem::getSoundVolume() const
{
	return soundVolume;
}

void SoundSystem::removeEmitter(EmitterData* emitter)
{
	auto it = std::find(emitters.begin(), emitters.end(), emitter);
	if (it != emitters.end())
	{
		delete* it;
		emitters.erase(it);
	}
}

void SoundSystem::removeListener()
{
	delete listener;
	listener = nullptr;
}

void SoundSystem::update(float deltaTime)
{
	Vector3 pos, forward, up;
	if (listener != nullptr)
	{
		pos = *listener->position;
		forward = GetForwardVector(*listener->quaternion);
		up = GetUpVector(*listener->quaternion);
		setListenerAttributes(pos, forward, up);
	}
	FMOD_VECTOR emitterPosition, zero;
	zero = { 0,0,0 };
	for (int i = 0; i < emitters.size(); i++)
	{
		bool paused = true;
		SoundSystem::EmitterData* data = emitters[i];
		for (auto it = data->channels.begin(); it != data->channels.end(); it++) {
			bool aux = (*it).second->paused;
			paused = paused && aux;
			if (!aux)
				(*it).second->channel->set3DAttributes(&emitterPosition, &zero);
		}
		if (!paused) emitterPosition = vecToFMOD(*data->position);
	}

	FMOD_RESULT result = system->update();
	ERRCHECK(result);
}

SoundSystem::EmitterData* SoundSystem::createEmitter(const Vector3* position)
{
	SoundSystem::EmitterData* data = new SoundSystem::EmitterData(position);
	emitters.push_back(data);
	return data;
}

SoundSystem::ListenerData* SoundSystem::createListener(const Vector3* position, const Vector4* quaternion)
{
	if (listener != nullptr)
		delete listener;
	ListenerData* data = new ListenerData();
	data->position = position;
	data->quaternion = quaternion;
	listener = data;
	return data;
}

FMOD_VECTOR SoundSystem::vecToFMOD(const Vector3& in)
{
	FMOD_VECTOR result;
	result.x = in.x;
	result.y = in.y;
	result.z = in.z;

	return result;
}

FMOD::Reverb3D* SoundSystem::createReverb()
{
	FMOD::Reverb3D* reverb;
	FMOD_RESULT result = system->createReverb3D(&reverb);
	ERRCHECK(result);
	return reverb;
}

void SoundSystem::ERRCHECK(FMOD_RESULT result) const
{
	if (result != FMOD_RESULT::FMOD_OK)
		LOG("%s", FMOD_ErrorString(result));
}

Sound* SoundSystem::getSound(const std::string& name) const
{
	Sound* sound = ResourcesManager::getSound(name);
	if (sound == nullptr) return nullptr;

	// Wait till loaded
	FMOD_OPENSTATE state;
	FMOD_RESULT result;
	do {
		result = sound->getOpenState(&state, nullptr, nullptr, nullptr);
	} while (state == FMOD_OPENSTATE_LOADING);

	if (result != FMOD_OK) {
		LOG("SOUND MANAGER: Error playing sound %s", name.c_str());
		ERRCHECK(result);
		return nullptr;
	}

	return sound;
}

SoundSystem::SoundChannel::~SoundChannel()
{
	channel = nullptr;
}

SoundSystem::SoundChannel::SoundChannel() : channel(nullptr), paused(false)
{

}

SoundSystem::SoundChannel::SoundChannel(Channel* channel) : channel(channel), paused(false)
{

}

SoundSystem::EmitterData::~EmitterData()
{
	for (auto it = channels.begin(); it != channels.end(); it++)
		delete it->second;
	channels.clear();
	position = nullptr;
}

SoundSystem::EmitterData::EmitterData(const Vector3* position) : position(position), channels(std::map<std::string, SoundChannel*>())
{

}

bool SoundSystem::EmitterData::isPaused()
{
	auto it = channels.begin();
	bool paused = true;
	while (paused && it != channels.end()) {
		paused = (*it).second->paused;
		it++;
	}

	return paused;
}