#pragma once

#ifndef WINDOW_MNGR
#define WINDOW_MNGR
#include <SDL.h>
#include <string>

class WindowManager
{
private:
    std::string gametittle_;
    int width_;
    int height_;

    SDL_Window* native = nullptr;
	SDL_Renderer* renderer_ = nullptr;

public:
    WindowManager(std::string gameTittle, int w, int h, bool fullScreen);
    WindowManager(const char* gameTittle, int w, int h, bool fullScreen);
    
    ~WindowManager();

    void createWindow();
    

    int getWidth() const;
    int getHeight() const;


};


#endif