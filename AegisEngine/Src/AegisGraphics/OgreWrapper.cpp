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

#include <SDL_syswm.h>
#include <OgreLogManager.h>
#include "./Components/Camera.h"

OgreWrapper::OgreWrapper() : mRoot(0),
mResourcesCfg(Ogre::BLANKSTRING),
mPluginsCfg(Ogre::BLANKSTRING)
{
}

bool OgreWrapper::Render() {
	return mRoot->renderOneFrame();
}


OgreWrapper::~OgreWrapper() {
	delete mRoot;
}

bool OgreWrapper::Init() {
	//files that contains the resources that ogre will use and the plugins used, specifically, Gl and D3D11 are
//added in order to have a render winow

	mResourcesCfg = "resources.cfg";
	mPluginsCfg = "plugins.cfg";

	Ogre::LogManager* lm = new Ogre::LogManager();
	bool writeInConsole = false;
	#if defined _DEBUG
		writeInConsole = true;
	#endif
	lm->createLog("./Logs/AegisOgreLog.txt", true, false, false);

	mRoot = new Ogre::Root(mPluginsCfg);

	Ogre::ConfigFile cf;
	cf.load(mResourcesCfg);

	Ogre::String name, locType;

	//we add all sections in resources.cfg (like [Essential]) and their list of locations to the ResourceGroupManager
	Ogre::ConfigFile::SettingsBySection_::const_iterator seci;
	for (seci = cf.getSettingsBySection().begin(); seci != cf.getSettingsBySection().end(); ++seci) {

		const Ogre::ConfigFile::SettingsMultiMap& settings = seci->second;
		Ogre::ConfigFile::SettingsMultiMap::const_iterator it;

		for (it = settings.begin(); it != settings.end(); it++) {
			//The name parameter is the path to the resources(i.e. "../media").The locType parameter defines what kind of location this is(i.e.Filesystem, Zip, etc.)
			locType = it->first;
			name = it->second;
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(name, locType);
		}
	}

	//creates an ogre.cfg in case there isn't one already
	if (!(mRoot->restoreConfig() || mRoot->showConfigDialog(nullptr)))
		return false;

	CreateWindowNative();
	Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);

	//initialise all resources found by ogre
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

	mSceneMgr = mRoot->createSceneManager();

	//scene camera

	//Ogre::SceneNode* ogreCam = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	//mCamera = mSceneMgr->createCamera("MainCam");
	//ogreCam->attachObject(mCamera);

	//viewPort
	auto ogreCamNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	mCamera = new AegisCamera("MainCamera",ogreCamNode);
	auto ogreCam = mCamera->GetCamera();
	Ogre::Viewport* vp = render->addViewport(ogreCam);

	ogreCamNode->setPosition(0, 0, 10);
	ogreCamNode->lookAt(Ogre::Vector3(0, 0, -300), Ogre::Node::TS_WORLD);
	ogreCam->setNearClipDistance(5);

	vp->setBackgroundColour(Ogre::ColourValue(0, 0, 0));

	ogreCam->setAspectRatio(
		Ogre::Real(vp->getActualWidth()) /
		Ogre::Real(vp->getActualHeight()));

	//fish creation with components
	//Ogre::SceneNode* fishNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	//Entity* fish = new Entity(fishNode);
	//fish->addComponent<Transform>("Transform", Vector3(), Vector4(), Vector3(1.0f, -1.0f, 1.0f));	
	//Renderer* fishRenderer = fish->addComponent<Renderer>("Renderer", fish, "fish.mesh", mSceneMgr, true);
	//fish->addComponent<Material>("Material", "red");
	//fishRenderer->render();

	mSceneMgr->setAmbientLight(Ogre::ColourValue(.5, .5, .5));

	//Scene's lightning
}

Ogre::SceneNode* OgreWrapper::GetRootNode()
{
	return mSceneMgr->getRootSceneNode()->createChildSceneNode();
}


void OgreWrapper::CreateWindowNative()
{
	mRoot->restoreConfig();
	mRoot->initialise(false);

	uint32_t w, h;
	Ogre::ConfigOptionMap ropts = mRoot->getRenderSystem()->getConfigOptions();

	std::istringstream mode(ropts["Video Mode"].currentValue);
	Ogre::String token;
	mode >> w; // width
	mode >> token; // 'x' as seperator between width and height
	mode >> h; // height
	Uint32 flags = SDL_WINDOW_RESIZABLE;
	if (!SDL_WasInit(SDL_INIT_VIDEO)) SDL_InitSubSystem(SDL_INIT_VIDEO);

	native = SDL_CreateWindow("SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, flags);

	SDL_SysWMinfo wmInfo;
	SDL_VERSION(&wmInfo.version);
	if (SDL_GetWindowWMInfo(native, &wmInfo) == SDL_FALSE) {
		OGRE_EXCEPT(Ogre::Exception::ERR_INTERNAL_ERROR,
			"Couldn't get WM Info! (SDL2)",
			"BaseApplication::setup");
	}

	Ogre::NameValuePairList params; // ogre window / render system params
	params.insert(std::make_pair("macAPI", "win"));
	params.insert(std::make_pair("macAPIWinUseNSView", "true"));

	// grab a string representing the NSWindow pointer
	Ogre::String winHandle = Ogre::StringConverter::toString((unsigned long)wmInfo.info.win.window);

	// assign the NSWindow pointer to the parentWindowHandle parameter
	params.insert(std::make_pair("parentWindowHandle", winHandle));

	render = mRoot->createRenderWindow("myWindowTitle", w, h, false, &params);
}
