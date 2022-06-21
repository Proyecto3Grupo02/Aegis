#pragma once

#ifndef AEGIS_MAIN_H 
#define AEGIS_MAIN_H

#include "IInitializable.h" 
//#include "../checkML.h"

class OgreWrapper;
class SceneManager;
class GameLoopData;
class LuaManager;

class AegisMain : IInitializable
{
private:
    OgreWrapper* ogreWrap;
    SceneManager* sceneManager;
    GameLoopData* gameLoopData;

    bool exit;
    //uint32_t frameTimeMS;

        void gameLoop();
        void convertObjectToLua();
    public:
        AegisMain();
        virtual ~AegisMain();
        virtual bool init() override;

        const float TARGET_FRAME_RATE = 60.0f;
    };
#endif //