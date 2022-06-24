#pragma once

#ifndef UI_OBJECT_H
#define UI_OBJECT_H

#include <string>
#include "LuaManager.h"
#include <functional>
//Imágenes renderizadas a partir de una textura
//En esta clase se añade la posición x e y

namespace Ogre {
	class OverlayContainer;
	class OverlayManager;
	class OverlaySystem;
	class Overlay;
}

//enum de metricas?
static int num_ui_obj = 0;

class UIObject {
protected:
	//Ogre::OverlaySystem* overlaySys = nullptr; //no esta inicializado
	Ogre::OverlayManager* overlayMng = nullptr;
	Ogre::OverlayContainer* overlayCont = nullptr;
	Ogre::Overlay* overlay = nullptr;
	float x, y, w, h;
	int zOrder;
	bool isVisible = true;
	int _id;

	template <class T>
	void setDataAsInnerType(T* component)
	{
		setType(luabridge::LuaRef(LuaManager::getInstance()->getState(), component));
	};

private:
	std::string material;
	std::string name;
	void show();
	void hide();
	luabridge::LuaRef type = LuaManager::getInstance()->getSharedEmptyLuaRef();
	luabridge::LuaRef data = LuaManager::getInstance()->getSharedEmptyLuaRef();
	std::function<void()> clickCallback;
	float scale;
public:
	UIObject(const std::string& n, int order, float x_, float y_, float w_, float h_, bool isActive = true, luabridge::LuaRef updateFuncl = LuaManager::getInstance()->getSharedEmptyLuaRef());
	UIObject(const std::string& n, int order, float x_, float y_, bool isActive = true, luabridge::LuaRef updateFuncl = LuaManager::getInstance()->getSharedEmptyLuaRef());
	virtual ~UIObject();
	
	//void setMetricsMode(MetricsMode mmode);
	void setVisible(bool visible);
	void setPosition(float x_, float y_);
	void setDimensions(float w_, float h_);
	void setMaterial(std::string m);
	void setRenderDepth(int d); //PROFUNDIDAD
	void setName(std::string n);
	void setType(luabridge::LuaRef t);
	void setClickCallback(std::function<void()> clickCallback);
	float getScale() const;
	void setScale(float scale);
	// Por si quieres hacer que un boton tenga una animacion de escalado o un texto se revele o cualquier otra cosa
	virtual void update(float deltaTime);
	bool onClick();
	luabridge::LuaRef getData() const;
	luabridge::LuaRef getType() const;
	luabridge::LuaRef updateFunc = LuaManager::getInstance()->getSharedEmptyLuaRef();
	int getZOrder();

	bool getVisible() { return isVisible; };
	std::string getName() { return name; };
	std::pair<float, float> getPosition() const { return { x, y }; }
	std::pair<float, float> getSize() const { return { w, h }; }
	std::string getMaterial() { return  material; }
	static void ConvertToLua(lua_State* state);
};

# endif
