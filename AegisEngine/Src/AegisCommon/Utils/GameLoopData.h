#pragma once

#ifndef TIMER_H
#define TIMER_H

#include <SDL_stdinc.h>
#include "Singleton.h"
//BASURA

struct GameLoopData : public Singleton<GameLoopData>
{
private:
	float deltaTime = 0;
	Uint32 frameStartTime = 0;
	Uint32 timeSinceAppStartMS = 0;
public:
	float getDeltaTime() { return deltaTime; }

	void setFrameStartTime(Uint32 startTime) { frameStartTime = startTime; }
	void setTimeSinceAppStartMS(Uint32 time) { timeSinceAppStartMS = time; }

	Uint32 getFrameStartTime() { return frameStartTime; }
	Uint32 getTimeSinceAppStartMS() { return timeSinceAppStartMS; }

	Uint32 UpdateTimeRegistry(Uint32 currentTime) {
		deltaTime = (currentTime - frameStartTime) / 1000.0f;
		timeSinceAppStartMS += (currentTime - frameStartTime);
		return deltaTime;
	}
};

inline GameLoopData* GameTime()
{
	return GameLoopData::getInstance();
}

# endif