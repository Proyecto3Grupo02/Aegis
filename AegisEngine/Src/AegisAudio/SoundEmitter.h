#pragma once

#ifndef SOUND_EMITTER_H
#define SOUND_EMITTER_H


#include "SoundSystem.h"
//namespace FMOD{
//	class Channel;
//}
typedef FMOD::Channel Channel;

struct Vector3;

class SoundEmitter
{

private:
	SoundSystem::EmitterData* emitterData;
	float pitch;
	float volume;

public:
	SoundEmitter();
	virtual ~SoundEmitter();

	void playSound(const std::string& soundName, bool reverb = false);
	void playMusic(const std::string& soundName, bool reverb = false);
	void stop(const std::string& sound);
	void pause(const std::string& sound);
	void resume(const std::string& sound);
	void stopAll();
	void pauseAll();
	void resumeAll();

	void setVolume(float volume);
	void setVolume(float volume, const std::string& sound);
	void setPitch(float pitch);
	void setPitch(float pitch, const std::string& sound);

	bool isPlaying(const std::string& soundName) const;
	void setPos(Vector3 position);

private:
	void setUpChannel(Channel* channel, bool reverb);
	Vector3 pos;

protected:
	//std::vector<std::pair<std::string, std::string>> properties;
	//void handleData(ComponentData* data);
};

#endif