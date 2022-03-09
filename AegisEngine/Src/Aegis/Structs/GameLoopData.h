#pragma once
#include <SDL_stdinc.h>

struct GameLoopData
{
public:
	Uint32 deltaTime = 0;

	Uint32 frameStartTime = 0;
	Uint32 timeSinceAppStart = 0;

	Uint32 UpdateDelta(Uint32 currentTime)
	{
		deltaTime = currentTime - frameStartTime;
		return deltaTime;
	}
};