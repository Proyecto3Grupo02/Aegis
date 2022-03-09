#pragma once
#include <OgreRoot.h>
#include "../Interfaces/IInitializable.h"

class OgreWrapper : IInitializable
{
private:
    Ogre::Root* mRoot;

    Ogre::String mResourcesCfg;
    Ogre::String mPluginsCfg;

    Ogre::RenderWindow* mWindow;
    Ogre::SceneManager* mSceneMgr;
    Ogre::Camera* mCamera;

public:
    OgreWrapper();
    virtual ~OgreWrapper();

    Ogre::SceneManager* getSceneMng() { return mSceneMgr; }

    bool Init() override;
};

