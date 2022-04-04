#pragma once
#ifndef OGRE_WRAPPER_H 
#define OGRE_WRAPPER_H

#include <OgreRoot.h>
#include <SDL.h>
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
    Ogre::Camera* mCamera;

    void CreateWindowNative();

public:
    OgreWrapper();
    bool Render();
    virtual ~OgreWrapper();
    bool Init();
    Ogre::SceneNode* GetRootNode();
};

#endif