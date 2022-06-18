
#pragma once
#include <string>
#include "OgreOverlay.h"
#include "Image.h"
#include "InputManager.h"
class Button : public Image
{
private:
	InputSystem* inputSystem = nullptr;
	bool wasClicked_ = false;

public:
	Button(const std::string& name, int order, std::string material, float x, float y, float w, float h);
	~Button() {};
	bool wasClicked();
	void update();
};
