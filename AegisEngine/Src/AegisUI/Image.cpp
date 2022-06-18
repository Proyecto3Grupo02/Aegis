#include "Image.h"

#include "OgreOverlay.h"
#include "OgreOverlayContainer.h"

#include<iostream>

Image::Image(const std::string& name, int order, std::string material, float x, float y, float w, float h)
	: UIObject(name, order, x, y, w, h) {
	overlayCont->setMaterialName(material);
	overlay->add2D(overlayCont);
	overlay->show(); //especifico de las imagenes?
	//std::cout << "imagen";
}

