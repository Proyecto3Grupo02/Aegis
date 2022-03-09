#include "InputSystem.h"

InputSystem::InputSystem() {

}

InputSystem::~InputSystem() {

}

void InputSystem::Init() {
	keys = std::vector<key>(256, { false, false, false });
}

void InputSystem::UpdateState() {
	for (int i = 0; i < keys.size(); i++) {
		if (keys[i].pressedThisFrame) {
			keys[i].pressedThisFrame = false;
			keys[i].down = true;
		}		

		keys[i].releasedThisFrame = false;
	}
}

void InputSystem::ClearState() {
	for (int i = 0; i < keys.size(); i++) {
		keys[i].pressedThisFrame = false;
		keys[i].down = false;
		keys[i].releasedThisFrame = false;
	}
}

int InputSystem::getId(SDL_Scancode key) {
	
	return 0;
}

//UPDATE KEY STATE-------------------------------------------------------
void InputSystem::OnKeyDown(SDL_Scancode key) {
	int i = getId(key);
	
	keys[i].pressedThisFrame = true;
	keys[i].down = false;
	keys[i].releasedThisFrame = false;
}

void InputSystem::OnKeyUp(SDL_Scancode key) {
	int i = getId(key);
	keys[i].pressedThisFrame = false;
	keys[i].down = false;
	keys[i].releasedThisFrame = true;
}

//CONSULT KEY STATE------------------------------------------------------------
bool InputSystem::isKeyDown(SDL_Scancode key) {
	int i = getId(key);
	return keys[i].down;
}

bool InputSystem::isKeyUp(SDL_Scancode key) {
	int i = getId(key);
	return keys[i].releasedThisFrame;
}

