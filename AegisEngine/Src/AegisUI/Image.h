#pragma once
#include "UIObject.h"

class Image : public UIObject
{
private:

public: //las imagenes necesitan recibir un material, no una imagen jpg/png
	Image(const std::string& name, int order, std::string material, Ogre::Overlay* o, float x, float y, float w, float h);
	~Image() {};
};

