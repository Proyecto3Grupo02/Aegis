#include <iostream>
#include "UIMain.h"
#include "UIObject.h"
#include "SDL_Image.h"
#include "SDL_render.h"


void UISystem::Init(SDL_Window* native) {
	std::cout << "SUUUUUUpuUUUU\n";
	rend = SDL_CreateRenderer(native, -1, SDL_RENDERER_ACCELERATED);
	//BORRAR (tanto la llamada como la declaración del método)
	metodoDePrueba();	
}

void UISystem::CreateUIObject(const std::string& filename, double textWidth, double textHeight, double x_, double y_, double w_, double h_){
	UIObject* obj = new UIObject(rend, filename, textWidth, textHeight, x_, y_, w_, h_);
	AddUIObject(obj);
}

void UISystem::AddUIObject(UIObject* object_) {
	ui_objects.push_back(object_);
}

void UISystem::DeleteUIObject(const UIObject* obj_) {
	std::vector<UIObject*>::iterator it = ui_objects.begin();

	while (it!= ui_objects.end()&&*it!=obj_) ++it;
	it = ui_objects.erase(it);
	
}

void UISystem::Render() {
	SDL_RenderClear(rend);
	for (auto o : ui_objects) o->render();
	SDL_RenderPresent(rend);
}

void UISystem::metodoDePrueba() {
	CreateUIObject("../logo_aegis.png", 650, 650, 0, 0, 100, 100);
}