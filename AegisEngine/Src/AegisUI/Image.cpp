#include "Image.h"

#include "OgreOverlay.h"
#include "OgreOverlayContainer.h"
#include "UISystem.h"

#include<iostream>

Image::Image(const std::string& name, int order, std::string material, float x, float y, float w, float h)
	: UIObject(name, order, x, y, w, h) {
	overlayCont->setMaterialName(material);
	overlay->add2D(overlayCont);
	overlay->show(); 
}

Image::~Image() {
}

Image* Image::CreateImage(LuaRef args) //Doesn't belong to this class
{//const std::string& name, int order, std::string material, float x, float y, float w, float h
	//std::string bodyName = ent->getName();
	std::string name = LuaMngr()->ParseString(args["name"], "Image" + id_img ); //PETA SI HAY MAS DE 1 CON EL MISMO NOMBRE ==> CUIDADO
	int order = LuaMngr()->ParseFloat(args["order"], 1);
	std::string material = LuaMngr()->ParseString(args["material"], "grass");
	float x = LuaMngr()->ParseFloat(args["x"], 1);
	float y = LuaMngr()->ParseFloat(args["y"], 1);
	float w = LuaMngr()->ParseFloat(args["width"], 1);
	float h = LuaMngr()->ParseFloat(args["height"], 1);
	id_img++;
	return new Image(name, order, material, x, y, w, h);
}
