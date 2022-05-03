#include "Text.h"



Text::Text(SDL_Renderer* rend, std::string text, Font* font, int longText) : Texture(rend), text_(text), font_(font), longText_(longText)
{
	createText(font, text);
}

void Text::createText(Font* font, std::string text)
{
	SDL_Surface* surface;
	surface = TTF_RenderText_Blended_Wrapped(font->getFont(), text.c_str(), { 255, 255, 255, 255 }, longText_);
	if (text != "") {

		if (surface == nullptr) {
			throw "Error  on surface"; // CHANGE TO PROPER EXCEPTION
		}
		else {
			cleanTexture();

			nCols = 1;
			nRows = 1;
			width = surface->w;
			height = surface->h;
			fWidth = width;
			fHeight = height;
			texture = SDL_CreateTextureFromSurface(renderer, surface);
			SDL_FreeSurface(surface);
		}
	}
}

void Text::setText(std::string text)
{
	if (text_ != text) {
		text_ = text;
		createText(font_, text);
	}
}

void Text::setSize(int size)
{
	if (font_->setFontSize(size))
		createText(font_, text_);
}

void Text::setFont(Font* font)
{
	if (font_ != font) {
		font_ = font;
		createText(font, text_);
	}
}

void Text::render(const SDL_Rect& dest) const
{
	if (text_ != "")
		Texture::render(dest);
}

Text::~Text()
{
	cleanTexture();
}