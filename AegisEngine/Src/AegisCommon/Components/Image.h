#pragma once
#include "../../AegisUI/Texture.h"
#include "UIComponent.h"
#include <string>

class RectTransform;
class Image: 
	public UIComponent {
public:
	Image(UIElement* elem, SDL_Renderer* rend,std::string filename, float w, float h, float angle);
	virtual ~Image();

	//void render() override;
protected:
	Texture* mTexture_;
	RectTransform* rect_;
	float width_, height_;
};

