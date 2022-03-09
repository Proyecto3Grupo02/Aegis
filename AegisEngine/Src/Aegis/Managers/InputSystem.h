#pragma once
#include "Singleton.h"
#include <vector>
#include<SDL.h>

class InputSystem : public Singleton<InputSystem> {
private:
    
    struct key {
        bool pressedThisFrame;
        bool down;
        bool releasedThisFrame;
    };
    std::vector<key> keys;
    std::pair<Sint32, Sint32> mousePos_;

public:
    
    InputSystem();
    ~InputSystem();
    void Init();
    void UpdateState();
    void ClearState();
    int getId(SDL_Scancode key); //keycode

    //UPDATE KEY STATE
    void OnKeyDown(SDL_Scancode key);
    void OnKeyUp(SDL_Scancode key);    

    //CONSULT KEY STATE
    bool isKeyUp(SDL_Scancode key);
    bool isKeyDown(SDL_Scancode key);


};