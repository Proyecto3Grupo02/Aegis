#include "Image.h"

#include "OgreOverlay.h"
#include "OgreOverlayManager.h"
#include "OgreOverlayContainer.h"
#include "OgreTextAreaOverlayElement.h"

#include<iostream>

Image::Image(const std::string& name, int order, std::string material, Ogre::Overlay* o) : UIObject(name, order,o) {
	overlayCont->setMaterialName(material);
	overlay->add2D(overlayCont);
	overlay->show(); //especifico de las imagenes?
	std::cout << "imagen";
}

