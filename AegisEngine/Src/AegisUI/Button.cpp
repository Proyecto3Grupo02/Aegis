#include "Button.h"
#include "UIMain.h"
#include <iostream>

Button::Button(const std::string& name, int order, std::string material,float x, float y, float w, float h)
	: Image(name, order, material, x, y, w, h) {
	inputSystem = UIs()->getInputSystem();
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