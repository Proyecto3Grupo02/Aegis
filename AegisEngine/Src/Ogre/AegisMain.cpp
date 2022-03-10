#include "AegisMain.h"
#include <OgreException.h>
#include <OgreConfigFile.h>
#include <OgreRenderWindow.h>
#include <OgreTextureManager.h>
#include <OgreSceneManager.h>
#include <OgreCamera.h>
#include <OgreViewport.h>
#include <OgreEntity.h>
#include <OgreSceneNode.h>

#include <iostream>
#include <fstream>

#include "OgreWrapper.h"
#include "Scene.h"
#include "GameLoopData.h"
#include <SDL.h>

//#include <sdlu>

void AegisMain::GameLoop()
{
	SDL_Event eventHandler;

	while (!exit)
	{
		gameLoopData->frameStartTime = SDL_GetTicks();

		while (SDL_PollEvent(&eventHandler) != 0)
		{
			if (eventHandler.type == SDL_KEYDOWN || eventHandler.type == SDL_QUIT)
				exit = true;
		}

		//gameLoopData += gameLoopData->GetDelta();
		//scene->UpdateScene(gameLoopData->deltaTime);

		Uint32 frameTime = gameLoopData->UpdateDelta(SDL_GetTicks());
		ogreWrap->Render();

		if (frameTime < 16)
			SDL_Delay(16 - frameTime);

	}
}

AegisMain::AegisMain() :
	ogreWrap(new OgreWrapper()), gameLoopData(new GameLoopData()), scene(new Scene()), exit(false)
{
}

AegisMain::~AegisMain()
{
	delete ogreWrap;
	delete scene;
	delete gameLoopData;
}

/// <summary>
/// Inicializa todos los wrappers (Ogre, Input, Imgui...)
/// </summary>
/// <returns></returns>
bool AegisMain::Init()
{
	ogreWrap->Init();
	GameLoop();

	return true;
}























//#include "AegisMain.h"
//
//#include <OgreEntity.h>
//#include <OgreCamera.h>
//#include <OgreViewport.h>
//#include <OgreSceneManager.h>
//#include <OgreRenderWindow.h>
//#include <OgreConfigFile.h>
//#include <OgreException.h>
//
//TutorialApplication::TutorialApplication()
//    : mRoot(0),
//    mResourcesCfg(Ogre::StringUtil::BLANK),
//    mPluginsCfg(Ogre::StringUtil::BLANK),
//    mWindow(0),
//    mSceneMgr(0),
//    mCamera(0)
//{
//}
//
//TutorialApplication::~TutorialApplication()
//{
//    //Ogre::WindowEventUtilities::removeWindowEventListener(mWindow, this);
//
//    windowClosed(mWindow);
//
//    delete mRoot;
//}
//
//bool TutorialApplication::go()
//{
//#ifdef _DEBUG
//    mResourcesCfg = "resources_d.cfg";
//    mPluginsCfg = "plugins_d.cfg";
//#else
//    mResourcesCfg = "resources.cfg";
//    mPluginsCfg = "plugins.cfg";
//#endif
//
//    mRoot = new Ogre::Root(mPluginsCfg);
//
//    Ogre::ConfigFile cf;
//    cf.load(mResourcesCfg);
//
//    Ogre::String name, locType;
//    Ogre::ConfigFile::SectionIterator secIt = cf.getSectionIterator();
//
//    while (secIt.hasMoreElements())
//    {
//        Ogre::ConfigFile::SettingsMultiMap* settings = secIt.getNext();
//        Ogre::ConfigFile::SettingsMultiMap::iterator it;
//
//        for (it = settings->begin(); it != settings->end(); ++it)
//        {
//            locType = it->first;
//            name = it->second;
//
//            Ogre::ResourceGroupManager::getSingleton().addResourceLocation(name, locType);
//        }
//    }
//
//    if (!(mRoot->restoreConfig() || mRoot->showConfigDialog()))
//        return false;
//
//    mWindow = mRoot->initialise(true, "TutorialApplication Render Window");
//
//    Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
//    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
//
//    mSceneMgr = mRoot->createSceneManager(Ogre::ST_GENERIC);
//
//    mCamera = mSceneMgr->createCamera("MainCam");
//    mCamera->setPosition(0, 0, 80);
//    mCamera->lookAt(0, 0, -300);
//    mCamera->setNearClipDistance(5);
//
//    Ogre::Viewport* vp = mWindow->addViewport(mCamera);
//    vp->setBackgroundColour(Ogre::ColourValue(0, 0, 0));
//
//    mCamera->setAspectRatio(
//        Ogre::Real(vp->getActualWidth()) /
//        Ogre::Real(vp->getActualHeight()));
//
//    // Create Scene
//    Ogre::Entity* ogreEntity = mSceneMgr->createEntity("ogrehead.mesh");
//
//    Ogre::SceneNode* ogreNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
//    ogreNode->attachObject(ogreEntity);
//
//    mSceneMgr->setAmbientLight(Ogre::ColourValue(.5, .5, .5));
//
//    Ogre::Light* light = mSceneMgr->createLight("MainLight");
//    light->setPosition(20, 80, 50);
//
//    // OIS
//    Ogre::LogManager::getSingletonPtr()->logMessage("*** Initializing OIS ***");
//
//    OIS::ParamList pl;
//    size_t windowHandle = 0;
//    std::ostringstream windowHandleStr;
//
//    mWindow->getCustomAttribute("WINDOW", &windowHandle);
//    windowHandleStr << windowHandle;
//    pl.insert(std::make_pair(std::string("WINDOW"), windowHandleStr.str()));
//
//    mInputMgr = OIS::InputManager::createInputSystem(pl);
//
//    mKeyboard = static_cast<OIS::Keyboard*>(
//        mInputMgr->createInputObject(OIS::OISKeyboard, false));
//    mMouse = static_cast<OIS::Mouse*>(
//        mInputMgr->createInputObject(OIS::OISMouse, false));
//
//    windowResized(mWindow);
//    Ogre::WindowEventUtilities::addWindowEventListener(mWindow, this);
//
//    mRoot->addFrameListener(this);
//
//    mRoot->startRendering();
//
//    return true;
//}
//
//
//
//#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
//#define WIN32_LEAN_AND_MEAN
//#include "windows.h"
//#endif
//
//#ifdef __cplusplus
//extern "C"
//{
//#endif
//
//#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
//    INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT)
//#else
//    int main(int argc, char* argv[])
//#endif
//    {
//        TutorialApplication app;
//
//        try
//        {
//            app.go();
//        }
//        catch (Ogre::Exception& e)
//        {
//#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
//            MessageBox(
//                NULL,
//                e.getFullDescription().c_str(),
//                "An exception has occured!",
//                MB_OK | MB_ICONERROR | MB_TASKMODAL);
//#else
//            std::cerr << "An exception has occured: " <<
//                e.getFullDescription().c_str() << std::endl;
//#endif
//        }
//
//        return 0;
//    }
//#ifdef __cplusplus
//}
//#endif