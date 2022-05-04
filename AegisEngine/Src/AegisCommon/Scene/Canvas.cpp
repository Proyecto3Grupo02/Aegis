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
	for (UIElement* elem : *mElems_)
		delete mElems_;

}

void Canvas::render()
{
	SDL_RenderClear(ogreWrapper->getRenderer());
	if (!mElems_->empty()) {
		for (auto* elem : *mElems_) {
			elem->render();
		}
	}

	SDL_RenderPresent(ogreWrapper->getRenderer());
	
}


//void Canvas::OnClickDown()
//{
//	for (auto* elem : *mElems_) {
//	//if(posicion dentro de mi y click)
//		elem->OnClickDown();
//	}
//}
//
//void Canvas::OnClickUp()
//{
//	for (auto* elem : *mElems_) {
//		elem->OnClickUp();
//	}
//}
//
//void Canvas::OnMouseOver()
//{
//	for (auto* elem : *mElems_) {
//		elem->OnMouseOver();
//	}
//}
//
//void Canvas::OnMouseExit()
//{
//	for (auto* elem : *mElems_) {
//		elem->OnMouseExit();
//	}
//}

void* Canvas::addUIElement(UIElement* elem)
{
	this->mElems_->push_back(elem);
}

void Canvas::ConvertToLua(lua_State* state)
{
	getGlobalNamespace(state).
		beginNamespace("Aegis").
		beginClass<Canvas>("Canvas").
		//addFunction("AddUIElement", &Canvas::addUIElement).
		endClass().
		endNamespace();
}
