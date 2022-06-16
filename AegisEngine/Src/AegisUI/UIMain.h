#pragma once
#include "Singleton.h"
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
	Ogre::OverlayManager* overlayMng;
	Ogre::OverlaySystem* overlaySys;
	Ogre::Overlay* overlay;

	std::vector<UIObject*>ui_objects;

	void AddUIObject(UIObject* object_);
public:
	void Init(Ogre::SceneManager* mScene);

	void CreateUIImage(const std::string& name, int order, std::string material);
	void DeleteUIObject(const UIObject* obj_);
};

inline UISystem* UIs()
{
	return UISystem::getInstance();
}