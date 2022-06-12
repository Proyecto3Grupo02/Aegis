#include "UIObject.h"

UIObject::UIObject(SDL_Renderer* rend, const std::string& filename, double textWidth, double textHeight, double x_, double y_, double w_, double h_) {
	texture = new Texture(rend, filename, textWidth, textHeight,0.0f);
	x = x_;
	y = y_;
	w = w_;
	h = h_;
}

UIObject::UIObject(double x_, double y_,double w_, double h_, Texture* texture_) {
	texture = texture_;
	x = x_;
	y = y_;
	w = w_;
	h = h_;
}


void UIObject::render() {
	SDL_Rect dest = { x,y,w,h };
	texture->render(dest);
}