#include "Text.h"
#include "OgreOverlay.h"
#include "OgreOverlayContainer.h"
#include "UISystem.h"
#include "OgreTextAreaOverlayElement.h"
#include "OgreOverlayManager.h"
#include "OgreFontManager.h"
#include<iostream>


Text::Text(const std::string name, int order, const std::string font, float charHeight, float x, float y, bool visible,
	const std::string text = "Example text") : UIObject(name, order, x, y, visible) {
	textArea = static_cast<Ogre::TextAreaOverlayElement*>(overlayMng->createOverlayElement("TextArea", "text"+ std::to_string(_id)));
	textArea->setCaption(text);
	textArea->setMetricsMode(Ogre::GMM_RELATIVE);
	setFontType(font);
	textArea->setCharHeight(charHeight);
	overlay->add2D(overlayCont);
	overlayCont->addChild(textArea);
	if (isVisible) overlay->show();
	else overlay->hide();

	SetDataAsInnerType(this);
}

Text::~Text() {
	//Destruye TextArea
	//overlayMng->destroy("text" + std::to_string(_id));
}

void Text::setText(const std::string& text_) {
	textArea->setCaption(text_);
}

std::string Text::getText()
{
	return textArea->getCaption();
}

void Text::setFontType(const std::string& font_) {
	try {
		textArea->setFontName(font_, "General");
	}
	catch (...) { 
		std::cout << "ERROR: Text::setFontType(): font_ " << font_ << " does not exist\n";
		textArea->setFontName("Font1", "General");
	};
}

void Text::setTextCharHeight(float ch_) {
	textArea->setCharHeight(ch_);
}

void Text::setFontColor(float r, float g, float b) {
	Ogre::ColourValue c = Ogre::ColourValue(r, g, b);
	textArea->setColour(c);
}

Text* Text::CreateText(LuaRef args) //Doesn't belong to this class
{//const std::string& name, int order, std::string material, float x, float y, float w, float h
	//std::string bodyName = ent->getName();
	std::string name = LuaMngr()->ParseString(args["name"], "Image" + num_text); //PETA SI HAY MAS DE 1 CON EL MISMO NOMBRE ==> CUIDADO
	int order = LuaMngr()->ParseFloat(args["order"], 1);
	std::string font = LuaMngr()->ParseString(args["material"], "Font1");
	float x = LuaMngr()->ParseFloat(args["x"], 1);
	float y = LuaMngr()->ParseFloat(args["y"], 1);
	float charHeight = LuaMngr()->ParseFloat(args["charheight"], 0.05f);
	bool isActive = LuaMngr()->ParseBool(args["visible"], true);
	std::string text = LuaMngr()->ParseString(args["text"], "Example text");
	num_text++;
	return new Text(name, order, font, charHeight, x, y, isActive, text);
}

void Text::ConvertToLua(lua_State* state)
{
	getGlobalNamespace(state).
		beginNamespace("Aegis").
		beginNamespace("UI").
		deriveClass<Text, UIObject>("UIText").
		addFunction("GetText", &Text::getText).
		addFunction("SetText", &Text::setText).
		addFunction("SetColor", &Text::setFontColor).
		endClass().
		endNamespace().
		endNamespace();
}
