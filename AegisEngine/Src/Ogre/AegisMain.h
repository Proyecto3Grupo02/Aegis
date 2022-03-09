#pragma once
#include "IInitializable.h"

class OgreWrapper;
class Scene;
struct GameLoopData;

class AegisMain : IInitializable
{
private:
    OgreWrapper* ogreWrap;
    Scene* scene;
    GameLoopData* gameLoopData;

    bool exit;

    void GameLoop();
public:
    AegisMain();
    virtual ~AegisMain();
    bool Init() override;
};



















//#pragma once
//#include <OgreRoot.h>
//#include <OgreRenderWindow.h>
//
//
//
//class TutorialApplication
//   
//{
//public:
//    TutorialApplication();
//    virtual ~TutorialApplication();
//
//    bool go();
//
//private:
//    virtual bool frameRenderingQueued(const Ogre::FrameEvent& fe);
//
//    virtual void windowResized(Ogre::RenderWindow* rw);
//    virtual void windowClosed(Ogre::RenderWindow* rw);
//
//    Ogre::Root* mRoot;
//    Ogre::String mResourcesCfg;
//    Ogre::String mPluginsCfg;
//    Ogre::RenderWindow* mWindow;
//    Ogre::SceneManager* mSceneMgr;
//    Ogre::Camera* mCamera;
//
//
//};
//
