#include "Button.h"
#include "UISystem.h"
#include <iostream>

Button::Button(const std::string& name, int order, std::string material, float x, float y, float w, float h, bool isActive, luabridge::LuaRef call, luabridge::LuaRef update)
	: Image(name, order, material, x, y, w, h, isActive, update) {
	inputSystem = UISystem::getInstance()->getInputSystem();
	windowManager = UISystem::getInstance()->getWindowManager();
	callback = call;
	id++;
	setDataAsInnerType(this);
	setClickCallback([this]() { buttonClickCallback(); });
}

Button::~Button() {
	//no hacer delete ni de inputSystem ni windowManager objviously
}

void Button::buttonClickCallback()
{
#if defined _DEBUG
	if (!callback.isNil())
	{
		try {
			callback(getData(), getType());
		}
		catch (LuaException const& e) {
			std::cout << e.what() << "\n";
		}

	}
#else
	if (!callback.isNil())
		callback(getData(),getType());
#endif
}

//LUA-----------------------------------------------------------------
Button* Button::CreateButton(LuaRef args) //Doesn't belong to this class
{//const std::string& name, int order, std::string material, float x, float y, float w, float h
	//std::string bodyName = ent->getName();
	std::string name = LuaMngr->parseString(args["name"], "Boton").append(std::to_string(id)); //PETA SI HAY MAS DE 1 CON EL MISMO NOMBRE ==> CUIDADO
	int order = LuaMngr->parseFloat(args["order"], 1);
	std::string material = LuaMngr->parseString(args["material"], "grass");
	float x = LuaMngr->parseFloat(args["x"], 1);
	float y = LuaMngr->parseFloat(args["y"], 1);
	float w = LuaMngr->parseFloat(args["width"], 1);
	float h = LuaMngr->parseFloat(args["height"], 1);
	bool isActive = LuaMngr->parseBool(args["visible"], true);
	id++;
	return new Button(name, order, material, x, y, w, h, isActive, args["callback"], args["updateFunc"]);
}

void Button::ConvertToLua(lua_State* state)
{
	getGlobalNamespace(state).
		beginNamespace("Aegis").
		beginNamespace("UI").
		deriveClass<Button, Image>("UIButton").
		endClass().
		endNamespace().
		endNamespace();
}
