#pragma once
#include "Texture.h"
#include "Font.h"
class Text :
	public Texture
{
public:
	Text(SDL_Renderer* rend);
	Text(SDL_Renderer* rend, std::string text, Font* font, int longText);
	void createText(Font* font, std::string text);

	Text(const Text&) = delete;
	Text operator=(const Text&) = delete;

	void setText(std::string text);
	void setSize(int size);
	void setFont(Font* font);
	void render(const SDL_Rect& dest) const;

	virtual ~Text();
protected:
	std::string text_ = "";
	Font* font_ = nullptr;
	int longText_ = 10;
};