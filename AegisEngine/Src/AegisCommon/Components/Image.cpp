#include "Image.h"
#include "../Entity/UIElement.h"
#include "RectTransform.h"
Image::Image(UIElement* elem, SDL_Renderer* rend, std::string filename, float w, float h, float angle):
	UIComponent("RenderImage")
{
	mTexture_ = new Texture(rend, filename,w,h,angle);
}

Image::~Image()
{
	delete mTexture_;
}

void Image::render()
{
	SDL_Rect dest;
	dest.x = getElement()->getRectTransform()->getPosition().x;
	dest.x = getElement()->getRectTransform()->getPosition().y;
	dest.w = width_;
	dest.h = height_;

	mTexture_->render(dest);
}
