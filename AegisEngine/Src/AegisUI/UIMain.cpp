#include <iostream>
#include "UIMain.h"
#include "UIObject.h"
#include "OgreOverlay.h"
#include "OgreOverlayPrerequisites.h"
#include "OgreTextAreaOverlayElement.h"
#include "OgreFontManager.h"
#include "OgreOverlayContainer.h"
#include "OgreOverlayElement.h"
#include "OgreOverlayManager.h"
#include "OgreSceneManager.h"
#include "OgreOverlaySystem.h"
#include "Image.h"

void UISystem::Init(Ogre::SceneManager* mScene) {
	
	overlaySys = new Ogre::OverlaySystem();
	overlayMng = Ogre::OverlayManager::getSingletonPtr();
	overlay = overlayMng->create("UI");
	//num = 0;
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
	mScene->addRenderQueueListener(overlaySys);
	
}

void UISystem::CreateUIImage(const std::string& name, int order, std::string material){
	Image* obj = new Image(name, order, material);
	AddUIObject(obj); //necesario????????????
}

void UISystem::AddUIObject(UIObject* object_) {
	ui_objects.push_back(object_);
}

void UISystem::DeleteUIObject(const UIObject* obj_) {
	std::vector<UIObject*>::iterator it = ui_objects.begin();

	while (it!= ui_objects.end()&&*it!=obj_) ++it;
	it = ui_objects.erase(it);	
}

