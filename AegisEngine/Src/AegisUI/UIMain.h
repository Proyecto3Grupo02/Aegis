#pragma once
#include "Singleton.h"
#include <vector>
#include "InputManager.h"
#include "../AegisScripting/Manager/LuaManager.h"

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

	void AddUIObject(UIObject* object_);
public:
	void CreateUIElem(luabridge::LuaRef luaref);
	void Init(Ogre::SceneManager* mScene, InputSystem* input);
	void DeleteUIObject(const UIObject* obj_);
	void Update(float deltaTime);
	InputSystem* getInputSystem();
	Ogre::Overlay* getOverlay();

	static void ConvertToLua(lua_State* state);
};

inline UISystem* UIs()
{
	return UISystem::getInstance();
}