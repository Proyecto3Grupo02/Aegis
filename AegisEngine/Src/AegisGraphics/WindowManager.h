#pragma once

#ifndef WINDOW_MNGR
#define WINDOW_MNGR
#include <SDL.h>
#include <string>
#include <OgreRoot.h>

class AegisCamera;
class WindowManager
{
private:
    std::string gametittle_;
    int width_;
    int height_;
    bool fullscreen;
    Uint32 flags;

    SDL_Window* mWindow_ = nullptr;
    Ogre::RenderWindow* render;
    AegisCamera* mCamera;
	

public:
    WindowManager(std::string gameTittle, int w, int h, bool fullScreen, Uint32 flag, Ogre::RenderWindow* rend, AegisCamera* cam);
    WindowManager(const char* gameTittle, int w, int h, bool fullScreen, Uint32 flag, Ogre::RenderWindow* rend, AegisCamera* cam);
    
    ~WindowManager();

    void createWindow();

    int getWidth() const;
    int getHeight() const;

    void update();


};


#endif