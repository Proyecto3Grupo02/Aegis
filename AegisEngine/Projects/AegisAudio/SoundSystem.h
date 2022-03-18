#pragma once
#pragma once
#ifndef SOUND_SYSTEM_H
#define SOUND_SYSTEM_H

#include "Singleton.h"

#include <fmod.hpp>
#include <map>
#include <vector>
#include <string>
#include "Quaternion.h"
#include <vector>
#include "Vector3.h"

typedef FMOD_MODE SoundMode;
typedef FMOD::Sound Sound;
typedef FMOD::System System;
typedef FMOD::Channel Channel;
typedef FMOD::ChannelGroup ChannelGroup;

class GAIA_API SoundSystem : public Singleton<SoundSystem>
{
	friend class GaiaCore;
	friend class Reverb;
	friend class ResourcesManager;
	friend class SoundEmitter;
	friend class SoundListener;
public:
	struct SoundChannel {
		Channel* channel;
		bool paused;

		SoundChannel();
		SoundChannel(Channel* channel);
		~SoundChannel();
	};
	struct EmitterData
	{
		std::map<std::string, SoundChannel*> channels;
		const Vector3* position;

		EmitterData(const Vector3* position);
		~EmitterData();
		bool isPaused();
	};
	struct ListenerData
	{
		const Vector3* position;
		const Quaternion* quaternion;
	};
private:
	System* system;

	ChannelGroup* music;
	ChannelGroup* soundEffects;

	float generalVolume;
	float soundVolume;
	float musicVolume;
	std::vector<EmitterData*> emitters;
	ListenerData* listener;

	void ERRCHECK(FMOD_RESULT result) const;

	Sound* getSound(const std::string& name) const;
public:
	SoundSystem();
	~SoundSystem();

	void setMusicVolume(float volume);
	void setSoundEffectsVolume(float volume);
	void setGeneralVolume(float volume);
	void setPauseAllSounds(bool pause);

	float getGeneralVolume() const;
	float getMusicVolume() const;
	float getSoundVolume() const;

private:
	void init();
	void close();

	Sound* createSound(const std::string& name, const SoundMode& mode);

	Channel* playSound(const std::string& name);
	Channel* playMusic(const std::string& name);

	void setListenerAttributes(const Vector3& position, const Vector3& forward, const Vector3& up);

	void removeEmitter(EmitterData* emitter);
	void removeListener();

	void update(float deltaTime);

	EmitterData* createEmitter(const Vector3* position);
	ListenerData* createListener(const Vector3* position, const Quaternion* quaternion);

	// Utils
	FMOD_VECTOR vecToFMOD(const Vector3& in);
	FMOD::Reverb3D* createReverb();
};

#endif