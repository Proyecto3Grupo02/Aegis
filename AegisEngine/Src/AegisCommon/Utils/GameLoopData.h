#pragma once
#include <SDL_stdinc.h>
#include "Singleton.h"
 //BASURA

struct TimeManager : public Singleton<TimeManager>
{
public:
	float deltaTime = 0;

	Uint32 frameStartTime = 0;
	Uint32 timeSinceAppStartMS = 0;

	Uint32 UpdateTimeRegistry(Uint32 currentTime) {
		deltaTime = (currentTime - frameStartTime) / 1000.0f;
		timeSinceAppStartMS += (currentTime - frameStartTime);
		return deltaTime;
	}
};

inline TimeManager* Time()
{
	return TimeManager::getInstance();
}