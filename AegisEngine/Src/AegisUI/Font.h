//#pragma once
//#include <string>
//#include "SDL_ttf.h"
//
//class Font
//{
//public:
//	//constructor
//	Font();
//	Font(const Font&) = delete;
//	Font operator=(const Font&) = delete;
//	Font(std::string path, int size, double widthRatio) { Loadfont(path, size, widthRatio); }
//
//	//destructor
//	virtual ~Font();
//
//	//change the font size to size
//	bool setFontSize(int size);
//
//	//change the current font to the path one
//	void changeFont(std::string path);
//	// Width of every character
//	void setWidthRatio(double width);
//	// Loads a font using these args
//	void Loadfont(std::string path, int size, double widthRatio);
//	inline TTF_Font* getFont() const { return font; }
//	inline double getWidthRatio() const { return widthRatio_; }
//	inline int getFontSize() const { return fontSize_; }
//
//	// Deletes this font
//	void ClearFont();
//
//protected:
//	TTF_Font* font;
//	int fontSize_;
//	std::string path_;
//	double widthRatio_;
//};