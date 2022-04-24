#pragma once 

#ifndef _SOUND_LISTENER
#define _SOUND_LISTENER

#include "SoundSystem.h"
#include "../../Dependencias/fmod/inc/fmod.hpp"
class SoundListener {
public:
	SoundListener(Vector3 pos, Vector4 quat);
	~SoundListener() {
		Audio()->removeListener();
	}

private:
	SoundSystem::ListenerData* listenData_;
};
#endif