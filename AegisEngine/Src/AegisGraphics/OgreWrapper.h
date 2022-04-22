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
    Ogre::LogManager* lm;
    
    void CreateWindowNative();

public:
    OgreWrapper();
    bool Render();
    virtual ~OgreWrapper();
    bool Init();
    AegisCamera* CreateCamera(Ogre::SceneNode* node = nullptr);
    Ogre::SceneNode* GetRootNode();
};

#endif