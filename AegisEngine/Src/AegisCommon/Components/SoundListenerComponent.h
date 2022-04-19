#pragma once 

#ifndef SOUND_LISTENER_H
#define SOUND_LISTENER_

#include "../../AegisAudio/SoundEmitter.h"
#include "AegisComponent.h"
#include "../Interfaces/ILuaObject.h"

class SoundListenerComponent: public AegisComponent
{
private:
    SoundListener* mListener_;
    
public:
    SoundListenerComponent(/* args */);
    ~SoundListenerComponent();

    static void ConvertToLua(lua_State* state);
};

SoundListenerComponent::SoundListenerComponent(/* args */)
{
}

SoundListenerComponent::~SoundListenerComponent()
{
}


#endif