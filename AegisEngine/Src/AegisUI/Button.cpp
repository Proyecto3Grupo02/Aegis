#include "Button.h"
#include "UISystem.h"
#include <iostream>

Button::Button(const std::string& name, int order, std::string material, float x, float y, float w, float h, bool isActive, luabridge::LuaRef call)
	: Image(name, order, material, x, y, w, h, isActive) {
	inputSystem = UISystem::getInstance()->getInputSystem();
	windowManager = UISystem::getInstance()->getWindowManager();
	callback = call;
	id++;
	setDataAsInnerType(this);
}

Button::~Button() {
	//no hacer delete ni de inputSystem ni windowManager objviously
}

void Button::update() {
	if (isVisible) {

		//comprobar que la posicion del raton (inputSystem) cae dentro de la imagen (metodos getpos y getsize)
		//este metodo tendria que ser llamado desde algun sitio siempre que se detecta click
		//La pos/w/h del boton pertenece al intervalo [0,1]. 
		//hay que multiplicarlo por las dimensiones de la ventana para obtener los atributos reales
		Vector2 mouseMotion = inputSystem->getMousePosition();
		Vector2 esquinaInf(x * windowManager->getWidth(), y * windowManager->getHeight());
		Vector2 esquinaSup(esquinaInf.getX() + w * windowManager->getWidth(), esquinaInf.getY() + h * windowManager->getHeight());

		//std::cout <<"PosRaton: "<< mouseMotion.getX() << " " << mouseMotion.getY() << "\n";
		//std::cout<<"Ventana: " << windowManager->getWidth() << " " << windowManager->getHeight() << "\n";
		///*std::cout << "Boton:" << x << " "<<y << "\n";
		//std::cout << "Esquina:" << x+w << " " << y+h << "\n";
		//std::cout << "Boton2:" << esquinaInf.getX() << " " << esquinaInf.getY() << "\n";
		//std::cout << "Esquina2:" << esquinaSup.getX() << " " << esquinaSup.getY() << "\n";*/

		if ((mouseMotion.getX() >= esquinaInf.getX() && mouseMotion.getX() <= esquinaSup.getX()) 
			&& mouseMotion.getY() >= esquinaInf.getY() && mouseMotion.getY() <= esquinaSup.getY()
			&& inputSystem->isMouseButtonPressedLua(0)) {
			std::cout << "- Button was clicked in C++\n";

			//PARA DEPURAR ==> CAPTURAR LA EXCEPCION PARA QUE TE DIGA DONDE FALLO EN LUA
			#if defined _DEBUG
			if (!callback.isNil())
			{
				try {
					callback(getData());
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
	std::string name = LuaMngr->parseString(args["name"], "Boton").append(std::to_string(id)); //PETA SI HAY MAS DE 1 CON EL MISMO NOMBRE ==> CUIDADO
	int order = LuaMngr->parseFloat(args["order"], 1);
	std::string material = LuaMngr->parseString(args["material"], "grass");
	float x = LuaMngr->parseFloat(args["x"], 1);
	float y = LuaMngr->parseFloat(args["y"], 1);
	float w = LuaMngr->parseFloat(args["width"], 1);
	float h = LuaMngr->parseFloat(args["height"], 1);
	bool isActive = LuaMngr->parseBool(args["visible"], true);
	id++;
	return new Button(name, order, material, x, y, w, h, isActive, args["callback"]);
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
