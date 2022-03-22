#pragma once
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
#include "Vector3.h"

typedef FMOD_MODE SoundMode;
typedef FMOD::Sound Sound;
typedef FMOD::System System;
typedef FMOD::Channel Channel;
typedef FMOD::ChannelGroup ChannelGroup;

class SoundSystem : public Singleton<SoundSystem>
{
	// Basic classes for fmod functionality
	friend class Core;
	friend class Reverb;
	friend class ResourcesManager;
	friend class SoundEmitter;
	friend class SoundListener;

public:
	// Canales par la emision de sonidos
	struct SoundChannel {
		Channel* channel;
		bool paused;

		SoundChannel();
		SoundChannel(Channel* channel);
		~SoundChannel();
	};

	// Datos necesarios para el emisor
	struct EmitterData
	{
		std::map<std::string, SoundChannel*> channels;
		const Vector3* position;

		EmitterData(const Vector3* position);
		~EmitterData();
		bool isPaused();
	};

	// Datos del listener (camara o player)
	// Permite la espacializacion 3d
	struct ListenerData
	{
		const Vector3* position;
		const Vector4* quaternion;
	};

private:
	System* system; // Initialization

	// Grupos de canales para distinguir musica y efectos
	ChannelGroup* music;
	ChannelGroup* soundEffects;

	float generalVolume; // Volumen para todo
	float soundVolume;	 // Volumen de efectos
	float musicVolume;	 // Volumen de musica

	// Vector para los emisores
	std::vector<EmitterData*> emitters;
	ListenerData* listener;

	void ERRCHECK(FMOD_RESULT result) const;

	// Funcion para obtener los sonidos desde recursos
	Sound* getSound(const std::string& name) const;

public:
	SoundSystem();
	~SoundSystem();

	// Setters y getters
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
	ListenerData* createListener(const Vector3* position, const Vector4* quaternion);

	// Utiles de Fmod
	FMOD_VECTOR vecToFMOD(const Vector3& in);
	FMOD::Reverb3D* createReverb();
};

#endif