#pragma once
#ifndef SOUND_SYSTEM_H
#define SOUND_SYSTEM_H

// AegisCommon
#include "Singleton.h"
#include "ILuaObject.h"

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
class SoundSystem : public Singleton<SoundSystem>, public ILuaObject
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
		FMOD_VECTOR position;

		EmitterData(FMOD_VECTOR position);
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
	std::map<std::string, ChannelGroup*> channelGroups;

	float generalVolume; // General game Volume

	// ECS structure; Manager functionality
	std::vector<EmitterData*> emitters;
	ListenerData* listener;
	SoundResources* SR;

	void ERRCHECK(FMOD_RESULT result) const;	// FMOD Errorcheck

	Sound* getSound(const std::string& name);	// Gets a sound from a resource

public:

	SoundSystem(std::string soundPaths);
	virtual ~SoundSystem();
	void update(float deltaTime);
	void close();
	
	// ChannelGroupControls
	void setPauseAllSounds(bool pause);
	
	void setGeneralVolume(float volume);
	float getGeneralVolume() const;

	void setChannelVolume(float volume, const std::string& channel);
	float getChannelVolume(const std::string channel);

	 
	Channel* playSound(const std::string& name, const std::string& channelName = "default");
	void stopChannel(EmitterData* emitterName, const std::string& name);
	void pauseSound(EmitterData* emitterName, const std::string& name);
	void resumeSound(EmitterData* emitterName, const std::string& name);

	void updatePosition(EmitterData* emitterName, Vector3 position);

	// ECS system classes
	FMOD::ChannelGroup* getChannelGroup(const std::string channelName);
	SoundChannel* createSoundChannel(Channel* channel);	
	EmitterData* createEmitter(const Vector3 position);
	void removeEmitter(EmitterData* emitter);
	ListenerData* createListener(Vector3* position, Vector4* quaternion);
	void removeListener();

	static void ConvertToLua(lua_State* state);

private:

	Sound* createSound(const std::string& name,  SoundMode mode);
	void setListenerAttributes(Vector3& position, Vector3& forward, Vector3& up);

	FMOD_VECTOR vecToFMOD(Vector3& in);
	FMOD::Reverb3D* createReverb();
};
#endif