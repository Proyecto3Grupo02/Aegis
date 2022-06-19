#include "Text.h"
#include "OgreOverlay.h"
#include "OgreOverlayContainer.h"
#include "UISystem.h"
#include "OgreTextAreaOverlayElement.h"
#include "OgreOverlayManager.h"
#include "OgreFontManager.h"
#include<iostream>


Text::Text(const std::string name, int order, const std::string font,float charHeight, float x, float y, float w,
	float h, float dx, float dy, const std::string text = "Example text") : UIObject(name, order, x, y, w, h, dx, dy) {
	textArea = static_cast<Ogre::TextAreaOverlayElement*>(overlayMng->createOverlayElement("TextArea", "text"+ std::to_string(num_text)));
	textArea->setCaption(text);
	textArea->setDimensions(dx, dy);
	textArea->setMetricsMode(Ogre::GMM_RELATIVE);
	setFontType(font);
	textArea->setCharHeight(charHeight);
	overlay->add2D(overlayCont);
	overlayCont->addChild(textArea);
	overlay->show();
}

Text::~Text() {

}

void Text::setText(const std::string& text_) {
	textArea->setCaption(text_);
}

void Text::setFontType(const std::string& font_) {
	try {
		textArea->setFontName(font_, "General");
	}
	catch (...) { std::cout << "ERROR: Text::setFontType(): font_ " << font_ << " does not exist\n"; };
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
	float w = LuaMngr()->ParseFloat(args["width"], 1);
	float h = LuaMngr()->ParseFloat(args["height"], 1);
	float dx = LuaMngr()->ParseFloat(args["dimensionx"], 1920);
	float dy = LuaMngr()->ParseFloat(args["dimensiony"], 1080);
	float charHeight = LuaMngr()->ParseFloat(args["charheight"], 0.05f);
	num_text++;
	return new Text(name, order, font, charHeight, x, y, w, h, dx, dy);
}