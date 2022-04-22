#include "InputManager.h"
#include <iostream>

InputSystem::InputSystem() {

}

InputSystem::~InputSystem() {

}

void InputSystem::Init() {
	keyNums = 322;
	keys = std::vector<key>(keyNums, { false, false, false });
}

void InputSystem::UpdateState() {

	KEY_WAS_PRESSED = false;
	KEY_WAS_RELEASED = false;
	KEY_DOWN = false;
	
	
	for (int i = 0; i < keyNums; i++) {
		keys[i].wasReleased = false;
		if (keys[i].wasPressed)
		{
			keys[i].wasPressed = false;
			keys[i].down = true;
			KEY_DOWN = true;
		}
	}
}

void InputSystem::ClearState() {
	for (int i = 0; i < keyNums; i++) {
		keys[i].wasPressed = false;
		keys[i].down = false;
		keys[i].wasReleased = false;
	}
}

int InputSystem::getId(SDL_Keycode key) {
	// Se clampea porque teclas especiales como Shift tienen valores fuera del array
	return SDL_clamp(key, 0, keyNums - 1);
}

//UPDATE KEY STATE-------------------------------------------------------
void InputSystem::OnKeyDown(SDL_Keycode key) {
	int i = getId(key);

	//SE PULSA POR PRIMERA VEZ
	if (!keys[i].wasPressed && !keys[i].down) {
		//std::cout << "111111\n";
		keys[i].wasPressed = true;
		KEY_WAS_PRESSED = true;
	}		

	//YA ESTBA PULSADA ==> QUEREMOS MANTENERLA

}

void InputSystem::OnKeyUp(SDL_Keycode key) {
	//std::cout << "33333333333\n";
	int i = getId(key);
	keys[i].wasPressed = false;
	keys[i].down = false;
	keys[i].wasReleased = true;
	KEY_WAS_RELEASED = true;
}

//CONSULTA GLOBAL----------------------------
bool InputSystem::oneKeyWasPressed() {
	return KEY_WAS_PRESSED;
}

bool InputSystem::oneKeyIsDown()
{
	return KEY_DOWN;
}

bool InputSystem::oneKeyWasReleased()
{
	return KEY_WAS_RELEASED;
}

//CONSULT KEY STATE------------------------------------------------------------
bool InputSystem::keyWasPressed(SDL_Keycode key) {
	int i = getId(key);
	return keys[i].wasPressed;
}

bool InputSystem::isKeyDown(SDL_Keycode key) {
	int i = getId(key);
	return keys[i].down;
}

bool InputSystem::keyWasReleased(SDL_Keycode key) {
	int i = getId(key);
	return keys[i].wasReleased;
}

//LUA-----------------------------------------------------
bool InputSystem::keyWasPressedLua(const char* key) {
	return keyWasPressed(SDL_GetKeyFromName(key));
}

bool InputSystem::isKeyDownLua(const char* key) {
	return isKeyDown(SDL_GetKeyFromName(key));
}

bool InputSystem::keyWasReleasedLua(const char* key) {
	return keyWasReleased(SDL_GetKeyFromName(key));
}

void InputSystem::ConvertToLua(lua_State* state)
{
	getGlobalNamespace(state).
		beginNamespace("Aegis").
			beginClass<InputSystem>("InputSystem").
				addFunction("KeyWasPressed", &InputSystem::keyWasPressedLua).
				addFunction("IsKeyDown", &InputSystem::isKeyDownLua).
				addFunction("KeyWasReleased", &InputSystem::keyWasReleasedLua).
				addFunction("AnyKeyWasPressed", &InputSystem::oneKeyWasPressed).
				addFunction("AnyKeyIsDown", &InputSystem::oneKeyIsDown).
				addFunction("AnyKeyWasReleased", &InputSystem::oneKeyWasReleased).
			endClass().
		endNamespace();
}

