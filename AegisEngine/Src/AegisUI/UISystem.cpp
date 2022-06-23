#include "UISystem.h"

#include "OgreOverlayManager.h"
#include "OgreSceneManager.h"
#include "OgreOverlaySystem.h"
#include "Button.h"
#include "Text.h"
#include "OgreFontManager.h"
#include <iostream>
#include "InputSystem.h"

#define inputSystem InputSystem::getInstance()

UISystem::UISystem(Ogre::SceneManager* mScene, WindowManager* window) : overlayMng(nullptr), overlaySys(nullptr) {
	if (mScene == nullptr)
	{
		SetInitializationFailed();
		return;
	}

	windowManager = window; //boton

	overlaySys = new Ogre::OverlaySystem();
	overlayMng = Ogre::OverlayManager::getSingletonPtr();
	overlay = overlayMng->create("UI");
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
	mScene->addRenderQueueListener(overlaySys);

	//LOADING FONTS
	Ogre::FontPtr pFont = Ogre::FontManager::getSingletonPtr()->create("Font1", "General");
	pFont->setType(Ogre::FT_TRUETYPE);
	pFont->setSource("WaterGalon.ttf");
	pFont->setTrueTypeSize(206);
	pFont->load();
}

UISystem::~UISystem() {
	for (auto uiObject : ui_objects)
	{
		delete uiObject;
		uiObject = nullptr;
	}

	ui_objects.clear();

	if (overlaySys != nullptr)
	{
		delete overlaySys;
		overlaySys = nullptr;
		//no hacer delete ni de inputSystem ni windowManager objviously
	}
}

Ogre::Overlay* UISystem::getOverlay() {
	return overlay;
}

InputSystem* UISystem::getInputSystem() {
	return inputSystem;
}

WindowManager* UISystem::getWindowManager() {
	return windowManager;
}

void UISystem::addUIObject(UIObject* object_) {
	ui_objects.push_back(object_);
}

void UISystem::deleteUIObject(const UIObject* obj_) {
	std::vector<UIObject*>::iterator it = ui_objects.begin();

	while (it != ui_objects.end() && *it != obj_) ++it;
	it = ui_objects.erase(it);
}

void UISystem::update(float deltaTime) {
	for (auto obj : ui_objects) {
		auto button = dynamic_cast<Button*>(obj);
		if (button != nullptr)button->update();
	}
}

//LUA----------------------------------------------------------------------------------
UIObject* UISystem::createUIElem(luabridge::LuaRef luaref) {
	std::string type = LuaMngr->parseString(luaref["type"], "nil");
	UIObject* uiObject = nullptr;

	if (type == "nil")
		return nullptr;
	else if (type == "Button") {
		uiObject = Button::CreateButton(luaref);
	}
	else if (type == "Image") {
		uiObject = Image::CreateImage(luaref);
	}
	else if (type == "Text") {
		uiObject = Text::CreateText(luaref);
	}

	if (uiObject != nullptr)
		addUIObject(uiObject);

	return uiObject;
}

void UISystem::ConvertToLua(lua_State* state) {
	getGlobalNamespace(state).
		beginNamespace("Aegis").
		beginNamespace("UI").
		beginClass<UISystem>("UISystem").
		addFunction("CreateUIElem", &UISystem::createUIElem).
		endClass().
		endNamespace().
		endNamespace();

	UIObject::ConvertToLua(state);
	Image::ConvertToLua(state);
	Text::ConvertToLua(state);
	Button::ConvertToLua(state);
}