#include "Font.h"


Font::Font() : font(nullptr), fontSize_(), path_(), widthRatio_()
{
}

//destructor
Font::~Font()
{
	ClearFont();
}

//change font size, returns false if the fontsize is equals to the size that we want to change
bool Font::setFontSize(int size)
{
	if (fontSize_ != size) {
		Loadfont(path_, size, widthRatio_);
		return true;
	}
	return false;
}

//changes the font
void Font::changeFont(std::string path)
{
	if (path_ != path) {
		Loadfont(path, fontSize_, widthRatio_);
	}
}

// Width of every character
void Font::setWidthRatio(double width)
{
	widthRatio_ = width;
}

// Loads a font using these args
void Font::Loadfont(std::string path, int size, double widthRatio)
{
	if (font != nullptr) ClearFont();
	font = TTF_OpenFont(path.c_str(), size);
	path_ = path;
	fontSize_ = size;
	widthRatio_ = widthRatio;
}

//deletes the font
void Font::ClearFont()
{
	TTF_CloseFont(font);
}