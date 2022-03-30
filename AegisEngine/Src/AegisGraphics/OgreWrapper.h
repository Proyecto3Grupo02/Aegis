#pragma once
#ifndef OGRE_WRAPPER_H 
#define OGRE_WRAPPER_H

#include <OgreRoot.h>
#include <SDL.h>
#include "../AegisCommon/Interfaces/IInitializable.h"

class OgreWrapper : IInitializable
{
private:
    Ogre::Root* mRoot;

    Ogre::String mResourcesCfg;
    Ogre::String mPluginsCfg;

    Ogre::RenderWindow* render = nullptr;
    SDL_Window* native = nullptr;

    Ogre::SceneManager* mSceneMgr;
    Ogre::Camera* mCamera;

    void CreateWindowNative();
public:
    OgreWrapper();
    bool Render();
    virtual ~OgreWrapper();
    bool Init() override;
    Ogre::SceneNode* GetRootNode();
};

#endif