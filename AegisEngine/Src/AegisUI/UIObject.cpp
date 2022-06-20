#include "UIObject.h"
#include <iostream>
#include "UISystem.h"
#include "OgreOverlay.h"
#include "OgreOverlayManager.h"
#include "OgreOverlayContainer.h"


UIObject::UIObject(const std::string& n, int order_, float x_, float y_) {
	overlayMng = Ogre::OverlayManager::getSingletonPtr();
	overlayCont = static_cast<Ogre::OverlayContainer*>(overlayMng->createOverlayElement("Panel", " PanelName" + std::to_string(num_ui_obj)));
	overlayCont->setMetricsMode(Ogre::GMM_RELATIVE);

	name = n; orden = order_;
	
	setPosition(x_, y_);
	w = h = 0;

	overlay = overlayMng->create(name + std::to_string(num_ui_obj));
	num_ui_obj++;
}

UIObject::UIObject(const std::string& n, int order, float x_, float y_, float w_, float h_) {
	overlayMng = Ogre::OverlayManager::getSingletonPtr();
	overlayCont = static_cast<Ogre::OverlayContainer*>(overlayMng->createOverlayElement("Panel", " PanelName" + std::to_string(num_ui_obj)));
	overlayCont->setMetricsMode(Ogre::GMM_RELATIVE);

	name = n; orden = order;
	
	//The setPosition() depends on w and h, so the first method must be setDimensions
	setDimensions(w_, h_); //dimension (1,1) = fullscreen
	setPosition(x_, y_); //position (0,0) = top left (1,1) = bottom right	

	overlay = overlayMng->create(name + std::to_string(num_ui_obj));
	num_ui_obj++;
}

UIObject::~UIObject() {
	//Destruye Overlay
	overlayMng->destroy(name + std::to_string(orden));
	//Destruye container
	overlayMng->destroyOverlayElement(overlayCont);
}

void UIObject::show() {
	overlay->show();
}

void UIObject::hide() {
	overlay->hide();
}

void UIObject::setActive(bool active) {
	isActive = active;
}

void UIObject::setPosition(float x_, float y_) {
	if (x_ + w >= 1)x = x_ - w;
	else x = x_;
	if (y_ + h >= 1)y = y_ - h;
	else y = y_;
	overlayCont->setPosition(x, y);	
}

void UIObject::setDimensions(float w_, float h_) {
	if (w_ > 1) {
		w = 1;
		std::cout << "WARNING: The width of the UI element is greater than 1. New width value = 1\n";
	}
	else if (w_ < 0) {
		w = 0;
		std::cout << "WARNING: The width of the UI element is lower than 0. New width value = 0\n";
	}
	else w = w_;
	if (h_ > 1) {
		h = 1;
		std::cout << "WARNING: The height of the UI element is greater than 1. New height value = 1\n";
	}
	else if (h_ < 0) {
		h = 0;
		std::cout << "WARNING: The height of the UI element is lower than 0. New height value = 0\n";
	}
	else h = h_;
	overlayCont->setDimensions(w, h);
}


void UIObject::setMaterial(std::string m) {
	overlayCont->setMaterialName(m);
	material = m;
}

void UIObject::setRenderDepth(int d) {
	if (overlay != nullptr)overlay->setZOrder(d);
	else std::cout << "OVERLAY EN UIOBJECT NO ESTA INICIALIZADO\n";
}

void UIObject::setName(std::string n) {
	name = n;
}

