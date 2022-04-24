#pragma once 

#ifndef _SOUND_LISTENER
#define _SOUND_LISTENER

#include "SoundSystem.h"
#include "../checkML.h"

// Creates a SoundListener on the SoundSystem
class SoundListener {

public:

	SoundListener();
	~SoundListener() {};

private:

	//SoundSystem::ListenerData* listenData_;
	Vector3 pos;
	Vector4 quat;

};

#endif