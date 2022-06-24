#pragma once
#ifndef IMAGE_H
#define IMAGE_H

#include "UIObject.h"
#include "InputSystem.h"
#include "LuaManager.h"

static int id_img = 0; // cada boton necesita tener un boton distinto

class Image : public UIObject {
private:
public: //las imagenes necesitan recibir un material, no una imagen jpg/png
	Image(const std::string& name, int order, std::string material, float x, float y, float w, float h, bool isActive, luabridge::LuaRef updateFunc);
	virtual ~Image();
	static Image* CreateImage(LuaRef args);
	static void ConvertToLua(lua_State* state);
};

# endif
