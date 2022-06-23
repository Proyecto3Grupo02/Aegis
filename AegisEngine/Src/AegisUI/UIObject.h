#pragma once

#ifndef UI_OBJECT_H
#define UI_OBJECT_H

#include <string>
#include "LuaManager.h"
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

public:
	UIObject(const std::string& n, int order, float x_, float y_, float w_, float h_, bool isActive = true);
	UIObject(const std::string& n, int order, float x_, float y_, bool isActive = true);
	virtual ~UIObject();
	
	//void setMetricsMode(MetricsMode mmode);
	void setVisible(bool visible);
	void setPosition(float x_, float y_);
	void setDimensions(float w_, float h_);
	void setMaterial(std::string m);
	void setRenderDepth(int d); //PROFUNDIDAD
	void setName(std::string n);
	void setType(luabridge::LuaRef t);
	luabridge::LuaRef getData() const;
	luabridge::LuaRef getType() const;

	bool getVisible() { return isVisible; };
	std::string getName() { return name; };
	std::pair<float, float> getPosition() { return { x, y }; }
	std::pair<float, float> getSize() { return { w, h }; }
	std::string getMaterial() { return  material; }
	static void ConvertToLua(lua_State* state);
};

# endif
