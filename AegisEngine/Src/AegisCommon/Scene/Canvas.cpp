#include "Canvas.h"
#include <sdl.h>
#include "../../AegisGraphics/OgreWrapper.h"
#include "../Entity/UIElement.h"
#include "../Utils/Vector2.h"
#include "../Components/Image.h"
Canvas::Canvas(OgreWrapper* wrap): ogreWrapper(wrap)
{
}

Canvas::~Canvas()
{

}

void Canvas::Init() {
	UIElement* elem = new UIElement(this, Vector2());
	//elem->addComponent<Image>("../Assets/Textures/panelfondo.png", 150,150);
}

void Canvas::render()
{
	SDL_RenderClear(ogreWrapper->getRenderer());

	for (auto* elem : *mElems_) {
		elem->render();
	}

	SDL_RenderPresent(ogreWrapper->getRenderer());
	
}


void Canvas::OnClickDown()
{
	for (auto* elem : *mElems_) {
	//if(posicion dentro de mi y click)
		elem->OnClickDown();
	}
}

void Canvas::OnClickUp()
{
	for (auto* elem : *mElems_) {
		elem->OnClickUp();
	}
}

void Canvas::OnMouseOver()
{
	for (auto* elem : *mElems_) {
		elem->OnMouseOver();
	}
}

void Canvas::OnMouseExit()
{
	for (auto* elem : *mElems_) {
		elem->OnMouseExit();
	}
}
