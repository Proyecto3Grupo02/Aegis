#pragma once

#ifndef UI_SYSTEM_H
#define UI_SYSTEM_H

#include "Singleton.h"
#include "InputManager.h"
#include "LuaManager.h"
#include <vector>

class OgreOverlay;
class SDL_Image; 
class UIObject;

namespace Ogre {
	class OverlayManager;
	class OverlaySystem;
	class Overlay;
	class SceneManager;
}

class UISystem : public Singleton<UISystem> {
private:
	InputSystem* inputSystem = nullptr; 
	Ogre::OverlayManager* overlayMng;
	Ogre::OverlaySystem* overlaySys;
	Ogre::Overlay* overlay;

	std::vector<UIObject*>ui_objects;

	void addUIObject(UIObject* object_);
public:
	UISystem();
	~UISystem();
	UIObject* createUIElem(luabridge::LuaRef luaref);
	void init(Ogre::SceneManager* mScene, InputSystem* input);
	void deleteUIObject(const UIObject* obj_);
	void update(float deltaTime);
	InputSystem* getInputSystem();
	Ogre::Overlay* getOverlay();

	static void ConvertToLua(lua_State* state);
};

inline UISystem* UIs()
{
	return UISystem::getInstance();
}

# endif