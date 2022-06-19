#include <iostream>
#include "UISystem.h"
#include "OgreOverlayManager.h"
#include "OgreSceneManager.h"
#include "OgreOverlaySystem.h"
#include "Button.h"
#include "Text.h"
#include "OgreFontManager.h"

UISystem::UISystem() {

}

UISystem::~UISystem() {
	std::vector<UIObject*>::iterator it = ui_objects.begin();

	while (!ui_objects.empty()) {
		it = ui_objects.erase(it);
	}	
}

void UISystem::Init(Ogre::SceneManager* mScene, InputSystem* input) {
	inputSystem = input; //boton

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


Ogre::Overlay* UISystem::getOverlay() {
	return overlay;
}

InputSystem* UISystem::getInputSystem() {
	return inputSystem;
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
	for (auto obj : ui_objects) {
		auto button = dynamic_cast<Button*>(obj);
		if (button != nullptr)button->update();
	}
}

//LUA----------------------------------------------------------------------------------
void UISystem::CreateUIElem(luabridge::LuaRef luaref) {
	std::string type = LuaMngr()->ParseString(luaref["type"], "nil");
	UIObject* uiObject = nullptr;

	if (type == "nil") 
		return;
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
		AddUIObject(uiObject);
}

void UISystem::ConvertToLua(lua_State* state) {
	getGlobalNamespace(state).
		beginNamespace("Aegis").
		beginNamespace("UI").
		beginClass<UISystem>("UISystem").
		addFunction("CreateUIElem", &UISystem::CreateUIElem).
		//deriveClass<ButtonComponent, AegisComponent>("Button").
		//addProperty("position", &RigidbodyComponent::GetPosition, &RigidbodyComponent::SetPosition).		
		//addFunction("wasClicked", &ButtonComponent::wasClicked).
		//addProperty("isActive", &ButtonComponent::isActive).
		endClass().
		endNamespace().
		endNamespace();
}