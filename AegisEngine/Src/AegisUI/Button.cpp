#include "Button.h"
#include "UIMain.h"
//#include "../AegisCommon/Entity/Entity.h"
#include <iostream>

Button::Button(const std::string& name, int order, std::string material,float x, float y, float w, float h)
	: Image(name, order, material, x, y, w, h) {
	inputSystem = UIs()->getInputSystem();
	id++;
}

void Button::update() {
	wasClicked_ = false;
	if (isActive) {	

		//comprobar que la posicion del raton (inputSystem) cae dentro de la imagen (metodos getpos y getsize)
		//este metodo tendria que ser llamado desde algun sitio siempre que se detecta click
		Vector2 mouseMotion = inputSystem->GetMousePosition();
		if ((mouseMotion.x >= x && mouseMotion.x <= x + w) && mouseMotion.y >= y && mouseMotion.y <= y + h
			&& inputSystem->IsMouseButtonPressedLua(0)) {
			std::cout << "Button was clicked\n";
			wasClicked_ = true;
		}
	}
}

bool Button::wasClicked() {
	return wasClicked_;
}

//LUA-----------------------------------------------------------------
Button* Button::CreateButton(LuaRef args) //Doesn't belong to this class
{//const std::string& name, int order, std::string material, float x, float y, float w, float h
	//std::string bodyName = ent->getName();
	std::string name = LuaMngr()->ParseString(args["name"], "Boton" + id); //PETA SI HAY MAS DE 1 CON EL MISMO NOMBRE ==> CUIDADO
	int order = LuaMngr()->ParseFloat(args["order"], 1);
	std::string material = LuaMngr()->ParseString(args["material"], "grass");
	float x = LuaMngr()->ParseFloat(args["x"], 1);
	float y = LuaMngr()->ParseFloat(args["y"], 1);
	float w = LuaMngr()->ParseFloat(args["width"], 1);
	float h = LuaMngr()->ParseFloat(args["height"], 1);

	return new Button(name, order, material, x, y, w, h);
}

//void Button::ConvertToLua(lua_State* state) {
//	getGlobalNamespace(state).
//		beginNamespace("Aegis").
//		beginNamespace("UI").
//		addFunction("CreateButton", CreateButton).
//		//deriveClass<Button, Image>("Button").
//		//addProperty("position", &RigidbodyComponent::GetPosition, &RigidbodyComponent::SetPosition).		
//		//addFunction("wasClicked", &Button::wasClicked).
//		//addProperty("isActive", &Button::isActive).
//		//endClass().
//		endNamespace().
//		endNamespace();
//}