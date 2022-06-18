#include <iostream>
#include "UIMain.h"
#include "OgreOverlayManager.h"
#include "OgreSceneManager.h"
#include "OgreOverlaySystem.h"
#include "Button.h"

void UISystem::Init(Ogre::SceneManager* mScene, InputSystem* input) {
	inputSystem = input; //boton

	overlaySys = new Ogre::OverlaySystem();
	overlayMng = Ogre::OverlayManager::getSingletonPtr();
	overlay = overlayMng->create("UI");

	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
	mScene->addRenderQueueListener(overlaySys);
	//CreateUIButton("ramon", 0, "grass");
	
}

Ogre::Overlay* UISystem::getOverlay() {
	return overlay;
}

InputSystem* UISystem::getInputSystem() {
	return inputSystem;
}

void UISystem::CreateUIButton(const std::string& name, int order, std::string material){
	//Button* obj = new Button(name, order, material, 10, 10, 40, 20);
	//AddUIObject(obj); //necesario????????????
}

void UISystem::AddUIObject(UIObject* object_) {
	ui_objects.push_back(object_);
}

void UISystem::DeleteUIObject(const UIObject* obj_) {
	std::vector<UIObject*>::iterator it = ui_objects.begin();

	while (it!= ui_objects.end()&&*it!=obj_) ++it;
	it = ui_objects.erase(it);	
}

void UISystem::Update(float deltaTime) {
	//for (auto obj : ui_objects) {
	//	auto button = dynamic_cast<Button*>(obj);
	//	if (button != nullptr)button->update();
	//}
}

