#include "WindowManager.h"
#include  "Components/Camera.h"
WindowManager::WindowManager(std::string gameTittle, int w, int h, bool fullScreen, Uint32 flag, Ogre::RenderWindow* rend, AegisCamera* cam) 
	
{
	WindowManager(gameTittle.c_str(), w, h, fullScreen, flag, rend, cam);
}

WindowManager::WindowManager(const char* gameTittle, int w, int h, bool fullScreen, Uint32 flag, Ogre::RenderWindow* rend, AegisCamera* cam):
	width_(w), height_(h), fullscreen(fullScreen),flags(flag),render(rend),mCamera(cam)
{
	mWindow_ = SDL_CreateWindow(gameTittle, 100, 100, w, h, flags);
	if (fullScreen) {
		SDL_SetWindowFullscreen(mWindow_, SDL_TRUE);
	}
	else {
		SDL_SetWindowFullscreen(mWindow_, SDL_FALSE);
	}
	mCamera->setViewport(0, 0, w, h);
}

WindowManager::~WindowManager()
{
}


int WindowManager::getWidth() const
{
	return 0;
}

int WindowManager::getHeight() const
{
	return 0;
}

void WindowManager::update()
{
}
