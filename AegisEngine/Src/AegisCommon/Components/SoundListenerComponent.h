#pragma once 

#ifndef SOUND_LISTENER_H
#define SOUND_LISTENER_

#include "SoundEmitter.h"
#include "AegisComponent.h"
#include "ILuaObject.h"
#include "SoundListener.h"

class SoundListenerComponent: public AegisComponent
{
private:
    SoundListener* mListener_;
    
public:
    SoundListenerComponent(/* args */);
    ~SoundListenerComponent();

    static void ConvertToLua(lua_State* state);
};


#endif