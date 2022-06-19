
#pragma once

#ifndef BUTTON_H
#define BUTTON_H

#include <string>
#include "OgreOverlay.h"
#include "Image.h"
#include "InputManager.h"
#include "LuaManager.h"

static int id = 0; // cada boton necesita tener un boton distinto

class Button : public Image
{
private:
	InputSystem* inputSystem = nullptr;
	luabridge::LuaRef callback = LuaMngr()->GetSharedEmptyLuaRef(); //necesistas inicializarlo

public:
	Button(const std::string& name, int order, std::string material, float x, float y, float w, float h, float dx, float dy, luabridge::LuaRef call);
	~Button();
	void update();
	static Button* CreateButton(LuaRef args);
};

# endif