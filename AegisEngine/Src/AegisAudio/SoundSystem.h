#pragma once
#ifndef SOUND_SYSTEM_H
#define SOUND_SYSTEM_H

// AegisCommon
#include "Singleton.h"

// Dependencies\Fmod
#include <fmod.hpp>

#include <map>
#include <vector>
#include <string>
#include "Vector3.h"	// AegisCommon
#include "Vector4.h"	// AegisCommon

#include "SoundResources.h"
//#include "../checkML.h"

// Typedef to avoid the use of Using
typedef FMOD_MODE SoundMode;		// Bit Descriptor mode
typedef FMOD::System System;		// Central FMOD system

typedef FMOD::Sound Sound;			// Sound to play
typedef FMOD::Channel Channel;		// Temporal channel for sound to play
typedef FMOD::ChannelGroup ChannelGroup;	// Common groups for utility


// Singleton Class
class SoundSystem : public Singleton<SoundSystem>
{
	// Basic classes for fmod functionality
	friend class Core;
	friend class Reverb;
	friend class ResourcesManager;
	friend class SoundEmitter;
	friend class SoundListener;

public:
	// Canales para la emision de sonidos
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

	// Camera/Player data for 3D enviroments
	struct ListenerData
	{
		 Vector3* position;
		 Vector4* quaternion;
	};

private:
	System* system; // FMOD Initialization
	
	// Group channels for menu volumes control
	ChannelGroup* music;
	ChannelGroup* soundEffects;

	float generalVolume; // General game Volume
	float soundVolume;	 // Sound channel volume
	float musicVolume;	 // Music channel volume

	// ECS structure; Manager functionality
	std::vector<EmitterData*> emitters;
	ListenerData* listener;
	SoundResources* SR;

	void ERRCHECK(FMOD_RESULT result) const;	// FMOD Errorcheck

	Sound* getSound(const std::string& name);	// Gets a sound from a resource

public:
	SoundSystem();
	virtual ~SoundSystem();

	// Setters y getters
	void setMusicVolume(float volume);
	void setSoundEffectsVolume(float volume);
	void setGeneralVolume(float volume);
	void setPauseAllSounds(bool pause);

	float getGeneralVolume() const;
	float getMusicVolume() const;
	float getSoundVolume() const;

	void close();
	Channel* playSound(const std::string& name);
	Channel* playMusic(const std::string& name);
private:
	

	Sound* createSound(const std::string& name,  SoundMode mode);

	void update(float deltaTime);
	void setListenerAttributes(Vector3& position, Vector3& forward, Vector3& up);

	void removeEmitter(EmitterData* emitter);
	void removeListener();

	// Utiles de Fmod
	FMOD_VECTOR vecToFMOD(Vector3& in);
	FMOD::Reverb3D* createReverb();

	// ECS system classes
	EmitterData* createEmitter(const Vector3* position);
	ListenerData* createListener( Vector3* position,  Vector4* quaternion);

};

inline SoundSystem* Audio()
{
	return SoundSystem::getInstance();
}

#endif