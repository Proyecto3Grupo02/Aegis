#include "UIObject.h"
#include <iostream>
#include "OgreOverlay.h"
#include "OgreOverlayManager.h"
#include "OgreOverlayElement.h"
#include "OgreOverlayContainer.h"

UIObject::UIObject(const std::string& n, int order) {
	name = n;
	overlayMng = Ogre::OverlayManager::getSingletonPtr();

	overlayCont = static_cast<Ogre::OverlayContainer*>(overlayMng->createOverlayElement("Panel", " PanelName" + std::to_string(order)));
	overlayCont->setMetricsMode(Ogre::GMM_PIXELS);
	overlayCont->setDimensions(500, 500);
	overlayCont->setPosition(100, 100);

	overlay = overlayMng->create(name + std::to_string(order));
	overlay->add2D(overlayCont);
	//set material
	//overlayCont->show(); //especifico de las imagenes?

	//overlaySys =
}

UIObject::~UIObject() {

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

void UIObject::setPosition(int x_, int y_) {
	overlayCont->setPosition(x_, y_);

	x = x_;
	y = y_;
}

//void UIObject::setDimensions(int dx, int dy) {
//	_overlayCont->setDimensions(dx, dy);
//}

void UIObject::setSize(int w_, int h_) {
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

