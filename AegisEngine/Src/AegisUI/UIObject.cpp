#include "UIObject.h"
#include <iostream>
#include "UISystem.h"
#include "OgreOverlay.h"
#include "OgreOverlayManager.h"
#include "OgreOverlayContainer.h"

UIObject::UIObject(const std::string& n, int order,float x_, float y_, float w_, float h_, float dx_, float dy_) {
	//UIs()->getOverlay();
	name = n;
	orden = order;
	x = x_; y = y_; w = w_;	h = h_; dx = dx_; dy = dy_;
	overlayMng = Ogre::OverlayManager::getSingletonPtr();
	overlayCont = static_cast<Ogre::OverlayContainer*>(overlayMng->createOverlayElement("Panel", " PanelName" + std::to_string(order)));
	overlayCont->setMetricsMode(Ogre::GMM_PIXELS);
	overlayCont->setPosition(x, y);
	overlayCont->setDimensions(dx, dy); //1920 x 1080
	overlayCont->setWidth(w);
	overlayCont->setWidth(h);

	overlay = overlayMng->create(name + std::to_string(order));
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

//void UIObject::setMetricsMode(MetricsMode mmode) {
//	switch (mmode) {
//	case GMM_PIXELS:
//		_overlayCont->setMetricsMode(Ogre::GMM_PIXELS);
//		break;
//	case GMM_RELATIVE:
//		_overlayCont->setMetricsMode(Ogre::GMM_RELATIVE);
//		break;
//	case GMM_RELATIVE_ASPECT_ADJUSTED:
//		_overlayCont->setMetricsMode(Ogre::GMM_RELATIVE_ASPECT_ADJUSTED);
//	}
//}

void UIObject::setActive(bool active) {
	isActive = active;
}

void UIObject::setPosition(float x_, float y_) {
	overlayCont->setPosition(x_, y_);

	x = x_;
	y = y_;
}

//void UIObject::setDimensions(int dx, int dy) {
//	_overlayCont->setDimensions(dx, dy);
//}

void UIObject::setSize(float w_, float h_) {
	overlayCont->setWidth(w_);
	overlayCont->setHeight(h_);

	w = w_;
	h = h_;
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

