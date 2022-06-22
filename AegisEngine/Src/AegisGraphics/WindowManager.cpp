#include "WindowManager.h"
#include  "AegisCamera.h"
#include <OgreRenderWindow.h>
#include <iostream>

WindowManager::WindowManager(std::string gameTittle, int w, int h, bool fullScreen, Uint32 flag) 
	
{
	WindowManager(gameTittle.c_str(), w, h, fullScreen, flag);
}

WindowManager::WindowManager(const char* gameTittle, int w, int h, bool fullScreen, Uint32 flag):
	width_(w), height_(h), fullscreen(fullScreen),flags(flag)
{
	mWindow_ = SDL_CreateWindow(gameTittle, 100, 100, w, h, flags);
	if (fullScreen) {
		SDL_SetWindowFullscreen(mWindow_, SDL_TRUE);
	}
	else {
		SDL_SetWindowFullscreen(mWindow_, SDL_FALSE);
	}
}

WindowManager::~WindowManager()
{
}


int WindowManager::getWidth() const
{
	return width_;
}

int WindowManager::getHeight() const
{
	return height_;
}

SDL_Window* WindowManager::getWindow() const
{
	return mWindow_;
}

void WindowManager::setRenderer(Ogre::RenderWindow* rend)
{
	render = rend;
}

void WindowManager::setCamera(AegisCamera* cam)
{
	mCamera = cam;
	//mCamera->setViewport(0, 0, width_, height_);
}

void WindowManager::update()
{
	SDL_Event evt ;

	while (SDL_PollEvent(&evt)) {
		////if (evt.type == SDL_WINDOWEVENT) {
		//	render->resize(evt.window.data1, evt.window.data2);
		//	width_ = evt.window.data1;
		//	height_ = evt.window.data2;
		////}
		//std::cout << width_<<" "<<height_<<"\n";
	}
}
