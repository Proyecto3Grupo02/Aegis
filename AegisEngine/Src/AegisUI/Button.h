
#pragma once

#ifndef BUTTON_H
#define BUTTON_H

#include <string>
#include "OgreOverlay.h"
#include "Image.h"
#include "WindowManager.h"
#include "LuaManager.h"

static int id = 0; // cada boton necesita tener un boton distinto

class Button : public Image
{
private:
	InputSystem* inputSystem = nullptr;
	WindowManager* windowManager = nullptr;
	luabridge::LuaRef callback = LuaMngr->getSharedEmptyLuaRef(); //necesistas inicializarlo

public:
	Button(const std::string& name, int order, std::string material, float x, float y, float w, float h, bool isActive, luabridge::LuaRef call, luabridge::LuaRef update);
	virtual ~Button();
	void buttonClickCallback();
	static Button* CreateButton(LuaRef args);
	static void ConvertToLua(lua_State* state);
};

# endif