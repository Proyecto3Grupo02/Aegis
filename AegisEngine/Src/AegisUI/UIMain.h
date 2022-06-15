#pragma once
#include "Singleton.h"
#include <vector>

class OgreOverlay;
class SDL_Image; 
struct SDL_Renderer;
class UIObject;
struct SDL_Window;


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
	//std::vector<UIElement*> _overlayElements;


	std::vector<UIObject*>ui_objects;
	void AddUIObject(UIObject* object_);
	SDL_Renderer* rend;
public:
	void Init(Ogre::SceneManager* mScene);
	//void update(float deltaTime, float timeStep, int maxSteps = 1);
	void Render();
	void CreateUIObject(const std::string& filename, double textWidth, double textHeight,
						double x_, double y_, double w_, double h_);
	void metodoDePrueba();
	void DeleteUIObject(const UIObject* obj_);
};

inline UISystem* UIs()
{
	return UISystem::getInstance();
}