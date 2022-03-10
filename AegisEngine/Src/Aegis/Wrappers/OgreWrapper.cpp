#include "OgreWrapper.h"

#include <OgreException.h>
#include <OgreConfigFile.h>
#include <OgreRenderWindow.h>
#include <OgreTextureManager.h>
#include <OgreSceneManager.h>
#include <OgreCamera.h>
#include <OgreViewport.h>
#include <OgreEntity.h>
#include <OgreSceneNode.h>

#include "Entity.h"
#include "Transform.h"
#include "Renderer.h"

OgreWrapper::OgreWrapper() : mRoot(0),
mResourcesCfg(Ogre::BLANKSTRING),
mPluginsCfg(Ogre::BLANKSTRING)
{
}


OgreWrapper::~OgreWrapper()
{
	delete mRoot;
}

bool OgreWrapper::Init()
{
    //files that contains the resources that ogre will use and the plugins used, specifically, Gl and D3D11 are
//added in order to have a render winow

    mResourcesCfg = "resources.cfg";
    mPluginsCfg = "plugins.cfg";


    mRoot = new Ogre::Root(mPluginsCfg);

    Ogre::ConfigFile cf;
    cf.load(mResourcesCfg);


    Ogre::String name, locType;

    //we add all sections in resources.cfg (like [Essential]) and their list of locations to the ResourceGroupManager
    Ogre::ConfigFile::SettingsBySection_::const_iterator seci;
    for (seci = cf.getSettingsBySection().begin(); seci != cf.getSettingsBySection().end(); ++seci) {

        const Ogre::ConfigFile::SettingsMultiMap& settings = seci->second;
        Ogre::ConfigFile::SettingsMultiMap::const_iterator it;

        for (it = settings.begin(); it != settings.end(); it++)
        {
            //The name parameter is the path to the resources(i.e. "../media").The locType parameter defines what kind of location this is(i.e.Filesystem, Zip, etc.)
            locType = it->first;
            name = it->second;
            Ogre::ResourceGroupManager::getSingleton().addResourceLocation(name, locType);
        }
    }

    //creates an ogre.cfg in case there isn't one already
    if (!(mRoot->restoreConfig() || mRoot->showConfigDialog(nullptr)))
        return false;

    mWindow = mRoot->initialise(true, "TutorialApplication Render Window");


    Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);

    //initialise all resources found by ogre
    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

    mSceneMgr = mRoot->createSceneManager();

    //scene camera

    Ogre::SceneNode* ogreCam = mSceneMgr->getRootSceneNode()->createChildSceneNode();
    mCamera = mSceneMgr->createCamera("MainCam");
    ogreCam->attachObject(mCamera);
    ogreCam->setPosition(0, 0, 20);
    ogreCam->lookAt(Ogre::Vector3(0, 0, -300), Ogre::Node::TS_WORLD);
    mCamera->setNearClipDistance(5);

    //viewPort
    Ogre::Viewport* vp = mWindow->addViewport(mCamera);

    vp->setBackgroundColour(Ogre::ColourValue(0, 0, 0));

    mCamera->setAspectRatio(
        Ogre::Real(vp->getActualWidth()) /
        Ogre::Real(vp->getActualHeight()));

    //fish creation
    //Ogre::Entity* ogreEntity = mSceneMgr->createEntity("fish.mesh");
    //Ogre::SceneNode* ogreNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
    //ogreNode->attachObject(ogreEntity);

    //fish creation with components
    Ogre::SceneNode* fishNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
    Entity* fish = new Entity(fishNode);
    fish->addComponent<Transform>(Vector3(), Vector4(), Vector3(1.0f, 1.0f, 1.0f));
    Renderer* fishRenderer = fish->addComponent<Renderer>(fish, "fish.mesh", mSceneMgr, true);
    fishRenderer->render();

    mSceneMgr->setAmbientLight(Ogre::ColourValue(.5, .5, .5));



    //Scene's lightning
    Ogre::SceneNode* ogreLight = mSceneMgr->getRootSceneNode()->createChildSceneNode();
    Ogre::Light* light = mSceneMgr->createLight("MainLight");
    ogreLight->attachObject(light);

    ogreLight->setPosition(-20, 80, 50);

    //dummy game's loop
    while (true) {

        if (mWindow->isClosed()) return false;

        if (!mRoot->renderOneFrame()) return false;
    }
}
