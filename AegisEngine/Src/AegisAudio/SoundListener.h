#pragma once 

#ifndef _SOUND_LISTENER
#define _SOUND_LISTENER

#include "SoundSystem.h"

class SoundListener {
public:
	SoundListener(Vector3 pos, Vector4 quat) {
		listenData_ = Audio()->createListener(new Vector3(pos), new Vector4(quat));
	}
	~SoundListener() {
		Audio()->removeListener();
	}

	






private:
	SoundSystem::ListenerData* listenData_;
};
#endif