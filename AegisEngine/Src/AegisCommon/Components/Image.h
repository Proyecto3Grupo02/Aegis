#pragma once

#include "UIComponent.h"
#include <string>
#include "../../AegisUI/Texture.h"
class UIElement;
class Texture;
class SDL_Renderer;
class RectTransform;
class Image: 
	public UIComponent {
public:
	Image(UIElement* elem, SDL_Renderer* rend,std::string& filename, float w, float h, float angle);
	 ~Image();

	void render() override;
protected:
	Texture* mTexture_;
	RectTransform* rect_;
	float width_, height_;
};

