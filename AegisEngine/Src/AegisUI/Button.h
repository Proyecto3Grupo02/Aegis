
#pragma once
#include <string>
#include "OgreOverlay.h"
#include "Image.h"
#include "../AegisCommon/Managers/InputManager.h"
class Button : public Image
{
private:
	InputSystem* inputSystem = nullptr;

public:
	Button(InputSystem* input, const std::string& name, int order, std::string material, Ogre::Overlay* o, float x, float y, float w, float h);
	~Button() {};
	bool wasClicked();

};
