#pragma once

#ifndef AEGIS_MAIN_H 
#define AEGIS_MAIN_H

#include "IInitializable.h" 

class OgreWrapper;

class AegisMain : IInitializable
{
private:
    OgreWrapper* ogreWrap;
    bool exit;

    void gameLoop();
    void convertObjectToLua();
    void free();

public:
    AegisMain();
    virtual ~AegisMain();
    virtual bool init() override;
    const float TARGET_FRAME_RATE = 60.0f;
    };
#endif //