#include "Button.h"

#include "Image.h"

Button::Button(InputSystem* input, const std::string& name, int order, std::string material, Ogre::Overlay* o, float x, float y, float w, float h)
	: Image(name, order, material, o, x, y, w, h) {
	inputSystem = input;

}

bool Button::wasClicked() {
	//comprobar que la posicion del raton (inputSystem) cae dentro de la imagen (metodos getpos y getsize)
	//este metodo tendria que ser llamado desde algun sitio siempre que se detecta click
	return false;
}
