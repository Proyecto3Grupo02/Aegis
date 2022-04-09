#pragma once 

#ifndef SOUNDEMITTER_H
#define SOUNDEMITTER_H
#include "AegisComponent.h"
#include "../../AegisAudio/SoundEmitter.h"
class SoundEmitterComponent: 
    public AegisComponent
{
private:
    SoundEmitter* mEmmiter_;
public:
    SoundEmitterComponent();
    ~SoundEmitterComponent();

    void playSound(const std::string& soundname,bool reverb = false);
    void playMusic(const std::string& soundname, bool reverb = false);

    void stop(const std::string& sound);
    void pause(const std::string& sound);
    void resume(const std::string& sound);

    void setVolume(const std::string& sound);
    void setPitch(float pitch);

    static void ConvertToLua(lua_State* state);

};

#endif