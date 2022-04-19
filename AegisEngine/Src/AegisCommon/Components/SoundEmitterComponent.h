#pragma once 

#ifndef SOUNDEMITTER_H
#define SOUNDEMITTER_H
#include "AegisComponent.h"
#include "../../AegisAudio/SoundEmitter.h"
class SoundEmitterComponent: 
    public AegisComponent
{
private:
    std::string mSound_;
    SoundEmitter* mEmmiter_;
public:
    SoundEmitterComponent(Entity* ent, std::string sound);
    ~SoundEmitterComponent();

    void playSound(const std::string& soundname,bool reverb = false);
    void playMusic(const std::string& soundname, bool reverb = false);

    std::string getSound() const;
    void setSound(std::string sound);

    void stop();
    void pause();
    void resume();

    void setVolume(float vol);
    void setPitch(float pitch);

    static void ConvertToLua(lua_State* state);


};

#endif