#include "Canvas.h"
#include <sdl.h>
#include "../../AegisGraphics/OgreWrapper.h"
#include "../Entity/UIElement.h"
Canvas::Canvas(OgreWrapper* wrap): ogreWrapper(wrap)
{
}

Canvas::~Canvas()
{
}

void Canvas::render()
{
	SDL_RenderClear(ogreWrapper->getRenderer());

	for (auto* elem : *mElems_) {
		elem->render();
	}

	SDL_RenderPresent(ogreWrapper->getRenderer());
	
}

void Canvas::update()
{

}

void Canvas::OnClickDown()
{
	for (auto* elem : *mElems_) {
		elem->render();
	}
}

void Canvas::OnClickUp()
{
	for (auto* elem : *mElems_) {
		
	}
}

void Canvas::OnMouseOver()
{
	for (auto* elem : *mElems_) {
		elem->render();
	}
}

void Canvas::OnMouseExit()
{
	for (auto* elem : *mElems_) {
		elem->render();
	}
}
