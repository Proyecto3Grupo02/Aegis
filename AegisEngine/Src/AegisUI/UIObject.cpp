#include "UIObject.h"
#include <iostream>
#include "UISystem.h"
#include "OgreOverlay.h"
#include "OgreOverlayManager.h"
#include "OgreOverlayContainer.h"
#include "InputSystem.h"

UIObject::UIObject(const std::string& n, int order_, float x_, float y_, bool visble, luabridge::LuaRef updateFuncl) : updateFunc(updateFuncl) {
	isVisible = visble;
	_id = num_ui_obj;
	overlayMng = Ogre::OverlayManager::getSingletonPtr();
	overlayCont = static_cast<Ogre::OverlayContainer*>(overlayMng->createOverlayElement("Panel", " PanelName" + std::to_string(num_ui_obj)));
	overlayCont->setMetricsMode(Ogre::GMM_RELATIVE);

	name = n; zOrder = order_;

	setPosition(x_, y_);
	w = h = 0;

	overlay = overlayMng->create(name + std::to_string(num_ui_obj));
	setRenderDepth(zOrder);
	num_ui_obj++;
	scale = 1;
}

UIObject::UIObject(const std::string& n, int order, float x_, float y_, float w_, float h_, bool visible, luabridge::LuaRef updateFuncl) : updateFunc(updateFuncl) {
	isVisible = visible;
	_id = num_ui_obj;
	overlayMng = Ogre::OverlayManager::getSingletonPtr();
	overlayCont = static_cast<Ogre::OverlayContainer*>(overlayMng->createOverlayElement("Panel", " PanelName" + std::to_string(num_ui_obj)));
	overlayCont->setMetricsMode(Ogre::GMM_RELATIVE);

	name = n; zOrder = order;

	//The setPosition() depends on w and h, so the first method must be setDimensions
	setDimensions(w_, h_); //dimension (1,1) = fullscreen
	setPosition(x_, y_); //position (0,0) = top left (1,1) = bottom right	
	overlay = overlayMng->create(name + std::to_string(num_ui_obj));
	setRenderDepth(zOrder);
	num_ui_obj++;

	this->data = LuaManager::getInstance()->getNewEmptyTable();
	scale = 1;
}

UIObject::~UIObject() {
	//Destruye Overlay
	overlayMng->destroy(name + std::to_string(_id));
	//Destruye container
	overlayMng->destroyOverlayElement(overlayCont);

	overlay = nullptr;
	overlayCont = nullptr;
	overlayMng = nullptr;
}

void UIObject::show() {
	overlay->show();
}

void UIObject::hide() {
	overlay->hide();
}

void UIObject::setVisible(bool visble_) {
	isVisible = visble_;
	if (isVisible) show();
	else hide();
}

void UIObject::setPosition(float x_, float y_) {
	if (x_ + w >= 1)x = x_ - w;
	else x = x_;
	if (y_ + h >= 1)y = y_ - h;
	else y = y_;
	overlayCont->setPosition(x, y);
}

void UIObject::setDimensions(float w_, float h_) {
	if (w_ > 1) {
		w = 1;
		std::cout << "WARNING: The width of the UI element is greater than 1. New width value = 1\n";
	}
	else if (w_ < 0) {
		w = 0;
		std::cout << "WARNING: The width of the UI element is lower than 0. New width value = 0\n";
	}
	else w = w_;
	if (h_ > 1) {
		h = 1;
		std::cout << "WARNING: The height of the UI element is greater than 1. New height value = 1\n";
	}
	else if (h_ < 0) {
		h = 0;
		std::cout << "WARNING: The height of the UI element is lower than 0. New height value = 0\n";
	}
	else h = h_;
	overlayCont->setDimensions(w, h);
}


void UIObject::setMaterial(std::string m) {
	overlayCont->setMaterialName(m);
	material = m;
	try {
		overlayCont->setMaterialName(m);
		material = m;
	}
	catch (...) {
		std::cout << " UIObject::setMaterial(): std::string m " << m << " does not exist. So material does not change\n";
	};
}

void UIObject::setRenderDepth(int d) {
	if (overlay != nullptr)overlay->setZOrder(d);
	else std::cout << "OVERLAY EN UIOBJECT NO ESTA INICIALIZADO\n";
}

void UIObject::setName(std::string n) {
	name = n;
}

void UIObject::setType(luabridge::LuaRef t)
{
	this->type = t;
}

void UIObject::setClickCallback(std::function<void()> clickCallback)
{
	this->clickCallback = clickCallback;
}

float UIObject::getScale() const
{
	return scale;
}

void UIObject::setScale(float scale)
{
	overlayCont->setDimensions(w * scale, h * scale);

	setPosition(x + (overlayCont->getWidth() - w * scale), y + (overlayCont->getHeight() - h * scale));
	this->scale = scale;
}

void UIObject::update(float deltaTime)
{
#if defined _DEBUG
	if (!updateFunc.isNil())
	{
		try {
			updateFunc(getData(), type, deltaTime);
		}
		catch (LuaException const& e) {
			std::cout << e.what() << "\n";
		}

	}
#else
	if (!updateFunc.isNil())
		updateFunc(getData(), type, deltaTime);
#endif
}

bool UIObject::onClick()
{
	if (overlay->isVisible()) {

		//comprobar que la posicion del raton (inputSystem) cae dentro de la imagen (metodos getpos y getsize)
		//este metodo tendria que ser llamado desde algun sitio siempre que se detecta click
		//La pos/w/h del boton pertenece al intervalo [0,1]. 
		//hay que multiplicarlo por las dimensiones de la ventana para obtener los atributos reales
		auto windowManager = UISystem::getInstance()->getWindowManager();
		auto inputSystem = InputSystem::getInstance();
		Vector2 mouseMotion = inputSystem->getMousePosition();
		Vector2 esquinaInf(x * windowManager->getWidth(), y * windowManager->getHeight());
		Vector2 esquinaSup(esquinaInf.getX() + w * windowManager->getWidth(), esquinaInf.getY() + h * windowManager->getHeight());

		if ((mouseMotion.getX() >= esquinaInf.getX() && mouseMotion.getX() <= esquinaSup.getX())
			&& mouseMotion.getY() >= esquinaInf.getY() && mouseMotion.getY() <= esquinaSup.getY() && clickCallback) {
				clickCallback();
				return true;
		}
	}

	return false;
}



luabridge::LuaRef UIObject::getData() const
{
	return this->data;
}

luabridge::LuaRef UIObject::getType() const
{
	return type;
}

int UIObject::getZOrder()
{
	return zOrder;
}

void UIObject::ConvertToLua(lua_State* state)
{
	luabridge::getGlobalNamespace(state).
		beginNamespace("Aegis").
		beginNamespace("UI").
		beginClass<UIObject>("UIObject").
		addFunction("SetVisible", &UIObject::setVisible).
		addFunction("GetName", &UIObject::getName).
		addFunction("SetScale", &UIObject::setScale).
		addFunction("GetScale", &UIObject::getScale).
		addProperty("position",
			std::function<Vector2(const UIObject*)>([](const UIObject* o)
				{
					auto pos = o->getPosition();
					return Vector2(pos.first, pos.second);
				}),
			std::function<void(UIObject*, Vector2)>([](UIObject* o, Vector2 v)
				{
					o->setPosition(v.getX(), v.getY());
				})
					).
		addProperty("type", &UIObject::getType, &UIObject::setType).
					addProperty("data", &UIObject::getData).
					endClass().
					endNamespace().
					endNamespace();
}

