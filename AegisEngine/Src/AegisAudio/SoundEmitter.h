#pragma once

#ifndef SOUND_EMITTER_H
#define SOUND_EMITTER_H

#include "AegisComponent.h"
#include "SoundSystem.h"

typedef SoundSystem::Channel Channel;

class SoundEmitter : public AegisComponent
{

private:
	SoundSystem::EmitterData* emitterData;
	float pitch;
	float volume;

public:
	SoundEmitter(Entity* entity);
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

private:
	void setUpChannel(Channel* channel, bool reverb);

protected:
	void handleData(ComponentData* data);
};

#endif