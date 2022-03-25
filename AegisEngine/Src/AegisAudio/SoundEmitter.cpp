#include "SoundEmitter.h"

#include "GameObject.h"
#include "ComponentRegister.h"
#include "../AegisCommon/Managers/DebugManager.h"



SoundEmitter::SoundEmitter(GameObject* gameObject) : AegisComponent(gameObject), emitterData(nullptr), pitch(0.0f), volume(0.0f)
{
	SoundSystem* soundSystem = SoundSystem::getInstance();

	emitterData = soundSystem->createEmitter(&gameObject->transform->getPosition());
	pitch = 1.0f;
	volume = 1.0f;
}

SoundEmitter::~SoundEmitter()
{
	SoundSystem* soundSystem = SoundSystem::getInstance();
	soundSystem->removeEmitter(emitterData);
}

void SoundEmitter::playSound(const std::string& soundName, bool reverb)
{
	stop(soundName);
	emitterData->channels[soundName] = new Channel(SoundSystem::getInstance()->playSound(soundName));
	setUpChannel(emitterData->channels[soundName], reverb);
}

void SoundEmitter::playMusic(const std::string& soundName, bool reverb)
{
	stop(soundName);
	emitterData->channels[soundName] = new Channel(SoundSystem::getInstance()->playMusic(soundName));
	setUpChannel(emitterData->channels[soundName], reverb);
}

void SoundEmitter::stop(const std::string& sound)
{
	auto it = emitterData->channels.find(sound);
	if (it != emitterData->channels.end()) {
		it->second->channel->stop();
		delete it->second;
		emitterData->channels.erase(it);
	}
}

void SoundEmitter::pause(const std::string& sound)
{
	bool p;
	auto it = emitterData->channels.find(sound);
	if (it != emitterData->channels.end()) {
		Channel* Channel = (*it).second;
		
		Channel->channel->getPaused(&p);
		if (!p) {
			Channel->channel->setPaused(true);
			Channel->paused = true;
		}
	}
}

void SoundEmitter::resume(const std::string& sound)
{
	bool p;
	auto it = emitterData->channels.find(sound);
	if (it != emitterData->channels.end()) {
		Channel* Channel = (*it).second;
		soundChannel->channel->getPaused(&p);
		if (p) {
			soundChannel->channel->setPaused(false);
			soundChannel->paused = false;
		}
	}
}

void SoundEmitter::stopAll()
{
	for (auto it = emitterData->channels.begin(); it != emitterData->channels.end();)
		stop((*it++).first);
}

void SoundEmitter::pauseAll()
{
	for (auto it = emitterData->channels.begin(); it != emitterData->channels.end(); it++)
		pause((*it).first);
}

void SoundEmitter::resumeAll()
{
	for (auto it = emitterData->channels.begin(); it != emitterData->channels.end(); it++)
		resume((*it).first);
}

void SoundEmitter::setVolume(float volume)
{
	this->volume = volume;
	for (auto it = emitterData->channels.begin(); it != emitterData->channels.end(); it++)
		setVolume(volume, (*it).first);
}

void SoundEmitter::setVolume(float volume, const std::string& sound)
{
	auto it = emitterData->channels.find(sound);
	if (it != emitterData->channels.end()) 
		(*it).second->channel->setVolume(volume);
}

void SoundEmitter::setPitch(float pitch)
{
	this->pitch = pitch;
	for (auto it = emitterData->channels.begin(); it != emitterData->channels.end(); it++)
		setPitch(pitch, (*it).first);
}

void SoundEmitter::setPitch(float pitch, const std::string& sound)
{
	auto it = emitterData->channels.find(sound);
	if (it != emitterData->channels.end())
		(*it).second->channel->setPitch(pitch);
}

bool SoundEmitter::isPlaying(const std::string& soundName) const
{
	bool playing = false;
	auto it = emitterData->channels.find(soundName);
	if (it != emitterData->channels.end())
		(*it).second->channel->isPlaying(&playing);
	return playing;
}

void SoundEmitter::setUpChannel(Channel* soundChannel, bool reverb)
{
	if (soundChannel != nullptr && soundChannel->channel != nullptr) {
		soundChannel->channel->setPitch(pitch);
		soundChannel->channel->setVolume(volume);

		if (!reverb)
			soundChannel->channel->setReverbProperties(0, 0);

		soundChannel->paused = false;
	}
}

void SoundEmitter::handleData(ComponentData* data)
{
	for (auto prop : data->getProperties()) {
		std::stringstream ss(prop.second);

		if (prop.first == "volume") {
			float volume;
			if (ss >> volume)
				setVolume(volume);
			else
				Debug()->Log("SOUND EMITTER: Wrong value for property %s", prop.first.c_str());
		}
		else if (prop.first == "pitch") {
			float pitch;
			if (ss >> pitch)
				setPitch(pitch);
			else
				Debug()->Log("SOUND EMITTER: Wrong value for property %s", prop.first.c_str());
		}
		else if (prop.first == "playSound")
		{
			playSound(prop.second, true);
		}
		else if (prop.first == "playMusic")
		{
			playMusic(prop.second);
		}
		else
		{
			Debug()->Log("SOUND EMITTER: Invalid property name \"%s\"", prop.first.c_str());
		}
	}

}