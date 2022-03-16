#pragma once

#ifndef AEGIS_MAIN_H 
#define AEGIS_MAIN_H

#include "IInitializable.h" //Da error en el cpp

class AegisOgre::OgreWrapper;
class AegisEngine::SceneManager;
class AegisUtils::GameLoopData;


using namespace AegisUtils;
namespace Aegis {
    class AegisMain : IInitializable
    {
    private:
        AegisOgre::OgreWrapper* ogreWrap;
        AegisEngine::SceneManager* sceneManager;
        AegisUtils::GameLoopData* gameLoopData;

        bool exit;
        //uint32_t frameTimeMS;

        void GameLoop();
    public:
        AegisMain();
        virtual ~AegisMain();
        virtual bool Init() override;

        const float TARGET_FRAME_RATE = 60.0f;
    };
}
#endif //

















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
