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
    Ogre::RenderWindow* render = nullptr;
    AegisCamera* mCamera = nullptr;

public:
    WindowManager(std::string gameTittle, int w, int h, bool fullScreen, Uint32 flag);
    WindowManager(const char* gameTittle, int w, int h, bool fullScreen, Uint32 flag);
    
    ~WindowManager();

    void createWindow();

    int getWidth() const;
    int getHeight() const;
    SDL_Window* getWindow() const;

    void setRenderer(Ogre::RenderWindow* rend);
    void setCamera(AegisCamera* cam);

    void handleEvent(SDL_Event& evt);
};

#endif