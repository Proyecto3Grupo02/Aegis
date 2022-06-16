#include "Image.h"

#include "OgreOverlay.h"
#include "OgreOverlayManager.h"
#include "OgreOverlayContainer.h"

#include<iostream>

Image::Image(const std::string& name, int order, std::string material) : UIObject(name, order) {
	overlayCont->setMaterialName(material);
	overlayCont->show(); //especifico de las imagenes?
std::cout << "imagen";
}

