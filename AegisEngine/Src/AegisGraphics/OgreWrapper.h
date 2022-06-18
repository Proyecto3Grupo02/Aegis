#pragma once
#ifndef OGRE_WRAPPER_H 
#define OGRE_WRAPPER_H

#include <OgreRoot.h>
#include <SDL.h>
#include "checkML.h"

class AegisCamera;
//BASURA

class OgreWrapper
{
private:
	Ogre::Root* mRoot;

	Ogre::String mResourcesCfg;
	Ogre::String mPluginsCfg;

	Ogre::RenderWindow* render = nullptr;
	SDL_Window* native = nullptr;
	SDL_Renderer* renderer_ = nullptr;

	static Ogre::SceneManager* mSceneMgr;
	Ogre::LogManager* lm;

	AegisCamera* mCamera;

	void CreateWindowNative();
	AegisCamera* CreateCamera(Ogre::SceneNode* node = nullptr);
public:
	OgreWrapper();
	AegisCamera* GetCamera();
	bool Render();
	virtual ~OgreWrapper();
	bool Init();
	Ogre::SceneNode* GetRootNode();

	inline SDL_Renderer* getRenderer()const { return renderer_; }
	inline SDL_Window* getNativeWindow()const {
		if (native != nullptr)
			return native;
		else throw "ERROR: native window from Ogre is nullptr";
	}

	static inline Ogre::SceneManager* getSceneManager() { return mSceneMgr; }
};

#endif