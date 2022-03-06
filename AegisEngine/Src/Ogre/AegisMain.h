#pragma once
#include <OgreRoot.h>

class AegisMain
{
private:
    Ogre::Root* mRoot;

    Ogre::String mResourcesCfg;
    Ogre::String mPluginsCfg;

    Ogre::RenderWindow* mWindow;
    Ogre::SceneManager* mSceneMgr;
    Ogre::Camera* mCamera;


public:
    AegisMain();
    virtual ~AegisMain();
    bool go();
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
