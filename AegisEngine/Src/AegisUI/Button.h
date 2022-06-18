
#pragma once
#include <string>
#include "OgreOverlay.h"
#include "Image.h"
#include "InputManager.h"
#include "../AegisScripting/Manager/LuaManager.h"

static int id = 0; // cada boton necesita tener un boton distinto

class Button : public Image
{
private:
	InputSystem* inputSystem = nullptr;
	//bool wasClicked_ = false;
	luabridge::LuaRef callback = LuaMngr()->GetSharedEmptyLuaRef(); //necesistas inicializarlo

public:
	Button(const std::string& name, int order, std::string material, float x, float y, float w, float h, luabridge::LuaRef call);
	~Button() {};
	//bool wasClicked();
	void update();
	static Button* CreateButton(LuaRef args);

	//LUA------------
	//static void ConvertToLua(lua_State* state);
};
