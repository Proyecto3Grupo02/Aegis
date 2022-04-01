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
	for (int i = 0; i < keyNums; i++) {
		keys[i].releasedThisFrame = false;
	}
	keydown = false;
	keyup = false;
	keypressed = false;

}

void InputSystem::ClearState() {
	for (int i = 0; i < keyNums; i++) {
		keys[i].pressedThisFrame = false;
		keys[i].down = false;
		keys[i].releasedThisFrame = false;
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
	if (!keys[i].pressedThisFrame && !keys[i].down) {
		//std::cout << "111111\n";
		keys[i].pressedThisFrame = true;
		keydown = true;
	}		

	//YA ESTBA PULSADA ==> QUEREMOS MANTENERLA
	else { 
		//std::cout << "22222222222222\n";
		keys[i].down = true;
		keys[i].pressedThisFrame = false;
		keypressed = true;
	}
}

bool InputSystem::isAnyKeyDown() {
	return keydown;
}
bool InputSystem::isAnyKeyUp()
{
	return keyup;
}
bool InputSystem::isAnyKeyPressed()
{
	return keypressed;
}
void InputSystem::OnKeyUp(SDL_Keycode key) {
	//std::cout << "33333333333\n";
	int i = getId(key);
	keys[i].pressedThisFrame = false;
	keys[i].down = false;
	keys[i].releasedThisFrame = true;
	keyup = true;
}


//CONSULT KEY STATE------------------------------------------------------------
bool InputSystem::isKeyPressedThisFrame(SDL_Keycode key)
{
	int i = getId(key);
	return keys[i].pressedThisFrame;
}

bool InputSystem::isKeyDown(SDL_Keycode key) {
	int i = getId(key);
	return keys[i].down;
}

bool InputSystem::isKeyUp(SDL_Keycode key) {
	int i = getId(key);
	return keys[i].releasedThisFrame;
}

//LUA-----------------------------------------------------
bool InputSystem::isKeyUpLua(const char* key)
{
	return isKeyUp(SDL_GetKeyFromName(key));
}

bool InputSystem::isKeyDownLua(const char* key)
{
	return isKeyDown(SDL_GetKeyFromName(key));
}

bool InputSystem::isKeyPressedThisFrameLua(const char* key)
{
	return isKeyPressedThisFrame(SDL_GetKeyFromName(key));
}

void InputSystem::ConvertToLua(lua_State* state)
{
	getGlobalNamespace(state).
		beginNamespace("ECS").
			beginClass<InputSystem>("InputSystem").
				addFunction("isKeyUp", &InputSystem::isKeyUpLua).
				addFunction("isKeyDown", &InputSystem::isKeyDownLua).
				addFunction("isKeyPressedThisFrame", &InputSystem::isKeyPressedThisFrameLua).
				addFunction("isAnyKeyDown", &InputSystem::isAnyKeyDown).
				addFunction("isAnyKeyPressed", &InputSystem::isAnyKeyPressed).
				addFunction("isAnyKeyUp", &InputSystem::isAnyKeyUp).
			endClass().
		endNamespace();
}

