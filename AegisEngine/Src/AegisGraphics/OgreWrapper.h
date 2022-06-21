#pragma once
#ifndef OGRE_WRAPPER_H 
#define OGRE_WRAPPER_H

#include <OgreRoot.h>
#include <SDL.h>

class AegisCamera;
class WindowManager;

class OgreWrapper
{
private:
	Ogre::Root* mRoot;

	Ogre::String mResourcesCfg;
	Ogre::String mPluginsCfg;

	Ogre::RenderWindow* render_ = nullptr;
	SDL_Window* native = nullptr;
	SDL_Renderer* renderer_ = nullptr;

	Ogre::SceneManager* mSceneMgr;
	Ogre::LogManager* lm;

	AegisCamera* mCamera;

	WindowManager* windowMan;

	void createWindowNative();
	AegisCamera* createCamera(Ogre::SceneNode* node = nullptr);

public:
	OgreWrapper();
	AegisCamera* getCamera();
	bool render();
	virtual ~OgreWrapper();
	bool init();
	Ogre::SceneNode* getRootNode();

	inline SDL_Renderer* getRenderer()const { return renderer_; }
	inline SDL_Window* getNativeWindow()const {
		if (native != nullptr)
			return native;
		else throw "ERROR: native window from Ogre is nullptr";
	}

	inline Ogre::SceneManager* getSceneManager() { return mSceneMgr; }
};

#endif