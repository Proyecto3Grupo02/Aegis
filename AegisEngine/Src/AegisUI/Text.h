#pragma once
#ifndef TEXT_H
#define TEXT_H

#include "UIObject.h"
#include "InputManager.h"
#include "LuaManager.h"

namespace Ogre {
	class TextAreaOverlayElement;
}

static int num_text = 0;
class Text : public UIObject {
private:
	Ogre::TextAreaOverlayElement* textArea = nullptr;
public:
	Text(const std::string name, int order, const std::string font, float charHeight, float x, float y, bool visible, const std::string text);
	~Text();

	void setText(const std::string& text_);
	std::string getText();
	void setFontType(const std::string& font_);
	void setTextCharHeight(float ch_);
	void setFontColor(float r, float g, float b);
	static Text* CreateText(LuaRef args);
	static void ConvertToLua(lua_State* state);
};


# endif
