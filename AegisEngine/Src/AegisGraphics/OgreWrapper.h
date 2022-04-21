#pragma once
#ifndef OGRE_WRAPPER_H 
#define OGRE_WRAPPER_H

#include <OgreRoot.h>
#include <SDL.h>
#include "../checkML.h"

class AegisCamera;
 //BASURA

class OgreWrapper
{
private:
    Ogre::Root* mRoot;

    Ogre::String mResourcesCfg;
    Ogre::String mPluginsCfg;

    Ogre::RenderWindow* render = nullptr;
    SDL_Window* native = nullptr;

    Ogre::SceneManager* mSceneMgr;
    AegisCamera* mCamera;
    Ogre::LogManager* lm;
    
    void CreateWindowNative();

public:
    OgreWrapper();
    bool Render();
    virtual ~OgreWrapper();
    bool Init();
    Ogre::SceneNode* GetRootNode();
};

#endif