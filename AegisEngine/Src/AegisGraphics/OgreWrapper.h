#pragma once
#ifndef OGRE_WRAPPER_H 
#define OGRE_WRAPPER_H

#include <OgreRoot.h>
#include <SDL.h>
#include "Singleton.h"

class AegisCamera;
class WindowManager;

class OgreWrapper : public Singleton<OgreWrapper>
{
private:
	Ogre::Root* mRoot = nullptr;

	Ogre::String mResourcesCfg;
	Ogre::String mPluginsCfg;

	Ogre::RenderWindow* render_ = nullptr;
	SDL_Window* native = nullptr;
	SDL_Renderer* renderer_ = nullptr;

	Ogre::SceneManager* mSceneMgr = nullptr;
	Ogre::LogManager* lm = nullptr;

	AegisCamera* mCamera = nullptr;

	WindowManager* windowMan = nullptr;

	void createWindowNative();
	AegisCamera* createCamera(Ogre::SceneNode* node = nullptr);
protected:
	bool init(std::string resourcesPath);
public:
	OgreWrapper(std::string pathToResourcesCfg);
	AegisCamera* getCamera();
	void handleEvent(SDL_Event& evt);
	bool render();
	virtual ~OgreWrapper();
	Ogre::SceneNode* getRootNode();

	inline SDL_Renderer* getRenderer()const { return renderer_; }
	inline SDL_Window* getNativeWindow()const {
		if (native != nullptr)
			return native;
		else throw "ERROR: native window from Ogre is nullptr";
	}

	inline Ogre::SceneManager* getSceneManager() { return mSceneMgr; }
	inline WindowManager* getWindowManager() { return windowMan; } //para el UISystem
};

#endif
