#pragma once

#ifndef UI_OBJECT_H
#define UI_OBJECT_H

#include <string>
//Imágenes renderizadas a partir de una textura
//En esta clase se añade la posición x e y

namespace Ogre {
	class OverlayContainer;
	class OverlayManager;
	class OverlaySystem;
	class Overlay;
}

//enum de metricas?
static int num_ui_obj = 0;

class UIObject {
protected:
	//Ogre::OverlaySystem* overlaySys = nullptr; //no esta inicializado
	Ogre::OverlayManager* overlayMng =nullptr;
	Ogre::OverlayContainer* overlayCont = nullptr;
	Ogre::Overlay* overlay = nullptr;
	float x, y, w, h, orden;
	bool isActive = true;

private:

	std::string material;
	std::string name;

public:
	UIObject(const std::string& n, int order, float x_, float y_, float w_, float h_);
	UIObject(const std::string& n, int order, float x_, float y_);
	virtual ~UIObject();

	void show();
	void hide();

	//void setMetricsMode(MetricsMode mmode);
	void setActive(bool active);
	void setPosition(float x_, float y_);
	void setDimensions(float w_, float h_);
	void setMaterial(std::string m);
	void setRenderDepth(int d); //PROFUNDIDAD
	void setName(std::string n);

	bool getActive() { return isActive; };
	std::string getName() { return name; };
	std::pair<float, float> getPosition() { return { x, y }; }
	std::pair<float, float> getSize() { return { w, h }; }
	std::string getMaterial() { return  material; }
	Ogre::Overlay* getOverlay() { return overlay; }
	//UIObject(double x_, double y_, double w_, double h_, Texture* texture_);

	//void render();
};

# endif