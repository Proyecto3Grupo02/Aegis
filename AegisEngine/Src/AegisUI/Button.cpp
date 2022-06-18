#include "Button.h"
#include "UISystem.h"
#include <iostream>

Button::Button(const std::string& name, int order, std::string material, float x, float y, float w, float h, float dx, float dy, luabridge::LuaRef call)
	: Image(name, order, material, x, y, w, h, dx, dy) {
	inputSystem = UIs()->getInputSystem();
	callback = call;
	id++;
}

void Button::update() {
	if (isActive) {

		//comprobar que la posicion del raton (inputSystem) cae dentro de la imagen (metodos getpos y getsize)
		//este metodo tendria que ser llamado desde algun sitio siempre que se detecta click
		Vector2 mouseMotion = inputSystem->GetMousePosition();
		if ((mouseMotion.x >= x && mouseMotion.x <= x + w) && mouseMotion.y >= y && mouseMotion.y <= y + h
			&& inputSystem->IsMouseButtonPressedLua(0)) {
			std::cout << "- Button was clicked in C++\n";

			//PARA DEPURAR ==> CAPTURAR LA EXCEPCION PARA QUE TE DIGA DONDE FALLO EN LUA
			#if defined _DEBUG
			if (!callback.isNil())
			{
				try {
					callback();
				}
				catch (LuaException const& e) {
					std::cout << e.what() << "\n";
				}

			}
			#else
			if (!callback.isNil())
				callback();
			#endif
		}
	}
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
	float dx = LuaMngr()->ParseFloat(args["dimensionx"], 1920);
	float dy = LuaMngr()->ParseFloat(args["dimensiony"], 1080);
	id++;
	return new Button(name, order, material, x, y, w, h, dx, dy, args["callback"]);
}