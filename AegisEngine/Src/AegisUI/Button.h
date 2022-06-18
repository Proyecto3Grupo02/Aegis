
#pragma once
#include <string>
#include "OgreOverlay.h"
#include "Image.h"
#include "InputManager.h"

//class Entity;

static int id = 0;

class Button : public Image
{
private:
	InputSystem* inputSystem = nullptr;
	bool wasClicked_ = false;

public:
	Button(const std::string& name, int order, std::string material, float x, float y, float w, float h);
	~Button() {};
	bool wasClicked();
	void update();
	static Button* CreateButton(LuaRef args);

	//LUA------------
	//static void ConvertToLua(lua_State* state);
};
