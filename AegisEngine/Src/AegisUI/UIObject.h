#pragma once
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


class UIObject {
protected:
	Ogre::OverlayManager* overlayMng =nullptr;
	Ogre::OverlayContainer* overlayCont = nullptr;
	Ogre::Overlay* overlay = nullptr;
	Ogre::OverlaySystem* overlaySys = nullptr; //no esta inicializado
	float x, y, w, h;
private:

	std::string material;
	std::string name;


public:
	UIObject(const std::string& n, int order, Ogre::Overlay* o, float x_, float y_, float w_, float h_);
	virtual ~UIObject();

	void show();
	void hide();

	//void setMetricsMode(MetricsMode mmode);
	void setPosition(float x, float y);
	void setScale(float x, float y);
	void setSize(float w, float h);
	void setMaterial(std::string m);
	void setRenderDepth(int d); //PROFUNDIDAD
	void setName(std::string n);

	std::string getName() { return name; };
	std::pair<float, float> getPosition() { return { x, y }; }
	std::pair<float, float> getSize() { return { w, h }; }
	std::string getMaterial() { return  material; }
	Ogre::Overlay* getOverlay() { return overlay; }
	//UIObject(double x_, double y_, double w_, double h_, Texture* texture_);

	//void render();
};

