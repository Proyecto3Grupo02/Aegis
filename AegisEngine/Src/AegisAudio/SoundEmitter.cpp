#include "SoundEmitter.h"


SoundEmitter::SoundEmitter() : emitterData_(nullptr), pitch(0.0f), volume(0.0f)
{
	SoundSystem* soundSystem = SoundSystem::getInstance();
	this->pos = Vector3(0);
	emitterData_ = soundSystem->createEmitter(&pos);
	pitch = 1.0f;
	volume = 1.0f;
}

SoundEmitter::~SoundEmitter()
{
	SoundSystem* soundSystem = SoundSystem::getInstance();
	soundSystem->removeEmitter(emitterData_);
}

void SoundEmitter::playSound(const std::string& soundName, bool reverb)
{
	stop(soundName);
	emitterData_->position = &pos;
	emitterData_->channels[soundName]->channel = SoundSystem::getInstance()->playSound(soundName);
	setUpChannel(emitterData_->channels[soundName]->channel, reverb);
}

void SoundEmitter::playMusic(const std::string& soundName, bool reverb)
{
	stop(soundName);	
	emitterData_->position = &pos;
	emitterData_->channels[soundName]->channel = SoundSystem::getInstance()->playMusic(soundName);
	setUpChannel(emitterData_->channels[soundName]->channel, reverb);
}

void SoundEmitter::stop(const std::string& sound)
{
	auto it = emitterData_->channels.find(sound);
	if (it != emitterData_->channels.end()) {
		it->second->channel->stop();
		delete it->second;
		emitterData_->channels.erase(it);
	}
}

void SoundEmitter::pause(const std::string& sound)
{
	bool p;
	auto it = emitterData_->channels.find(sound);
	if (it != emitterData_->channels.end()) {
		Channel* Channel = (*it).second->channel;
		
		Channel->getPaused(&p);
		if (!p) {
			Channel->setPaused(true);
			
		}
	}
}

void SoundEmitter::resume(const std::string& sound)
{
	bool p;
	auto it = emitterData_->channels.find(sound);
	if (it != emitterData_->channels.end()) {
		Channel* Channel = (*it).second->channel;
		Channel->getPaused(&p);
		if (p) {
			Channel->setPaused(false);
			
		}
	}
}

void SoundEmitter::stopAll()
{
	for (auto it = emitterData_->channels.begin(); it != emitterData_->channels.end();)
		stop((*it++).first);
}

void SoundEmitter::pauseAll()
{
	for (auto it = emitterData_->channels.begin(); it != emitterData_->channels.end(); it++)
		pause((*it).first);
}

void SoundEmitter::resumeAll()
{
	for (auto it = emitterData_->channels.begin(); it != emitterData_->channels.end(); it++)
		resume((*it).first);
}

void SoundEmitter::setVolume(float volume)
{
	this->volume = volume;
	for (auto it = emitterData_->channels.begin(); it != emitterData_->channels.end(); it++)
		setVolume(volume, (*it).first);
}

void SoundEmitter::setVolume(float volume, const std::string& sound)
{
	auto it = emitterData_->channels.find(sound);
	if (it != emitterData_->channels.end()) 
		(*it).second->channel->setVolume(volume);
}

void SoundEmitter::setPitch(float pitch)
{
	this->pitch = pitch;
	for (auto it = emitterData_->channels.begin(); it != emitterData_->channels.end(); it++)
		setPitch(pitch, (*it).first);
}

void SoundEmitter::setPitch(float pitch, const std::string& sound)
{
	auto it = emitterData_->channels.find(sound);
	if (it != emitterData_->channels.end())
		(*it).second->channel->setPitch(pitch);
}

bool SoundEmitter::isPlaying(const std::string& soundName) const
{
	bool playing = false;
	auto it = emitterData_->channels.find(soundName);
	if (it != emitterData_->channels.end())
		(*it).second->channel->isPlaying(&playing);
	return playing;
}

void SoundEmitter::setPos(Vector3 position)
{
	this->pos = position;
}

void SoundEmitter::setUpChannel(Channel* soundChannel, bool reverb)
{
	if (soundChannel != nullptr) {
		soundChannel->setPitch(pitch);
		soundChannel->setVolume(volume);

		if (!reverb)
			soundChannel->setReverbProperties(0, 0);

		soundChannel->setPaused(false);
	}
}
/* ¿Es necesario?
void SoundEmitter::handleData(ComponentData* data)
{
	for (auto prop : data->getProperties()) {
		std::stringstream ss(prop.second);

		if (prop.first == "volume") {
			float volume;
			if (ss >> volume)
				setVolume(volume);
			else
				DebugManager::getInstance()->Log("SOUND EMITTER: Wrong value for property %s", prop.first.c_str());
		}
		else if (prop.first == "pitch") {
			float pitch;
			if (ss >> pitch)
				setPitch(pitch);
			else
				DebugManager::getInstance()->Log("SOUND EMITTER: Wrong value for property %s", prop.first.c_str());
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
			DebugManager::getInstance()->Log("SOUND EMITTER: Invalid property name \"%s\"", prop.first.c_str());
		}
	}

}*/