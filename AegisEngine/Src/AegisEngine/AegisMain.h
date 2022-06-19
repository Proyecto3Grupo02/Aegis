#pragma once

#ifndef AEGIS_MAIN_H 
#define AEGIS_MAIN_H

#include "IInitializable.h" 
//#include "../checkML.h"

class OgreWrapper;
class SceneManager;
class TimeManager;
class LuaManager;

class AegisMain : IInitializable
{
private:
    OgreWrapper* ogreWrap;
    SceneManager* sceneManager;
    TimeManager* gameLoopData;

    bool exit;
    //uint32_t frameTimeMS;

        void GameLoop();
        void ConvertObjectToLua();
    public:
        AegisMain();
        virtual ~AegisMain();
        virtual bool Init() override;

        const float TARGET_FRAME_RATE = 60.0f;
    };
#endif //