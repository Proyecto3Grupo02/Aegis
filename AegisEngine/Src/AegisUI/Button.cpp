#include "Button.h"


Button::Button(InputSystem* input, const std::string& name, int order, std::string material, Ogre::Overlay* o, float x, float y, float w, float h)
	: Image(name, order, material, o, x, y, w, h) {
	inputSystem = input;
}

bool Button::wasClicked() {
	//comprobar que la posicion del raton (inputSystem) cae dentro de la imagen (metodos getpos y getsize)
	//este metodo tendria que ser llamado desde algun sitio siempre que se detecta click
	Vector2 mouseMotion = inputSystem->GetMousePosition();
	if ((mouseMotion.x >= x && mouseMotion.x <= x + w) && mouseMotion.y >= y && mouseMotion.y <= y + h
		&& inputSystem->IsMouseButtonPressedLua(0))
		return true;
	return false;
}
