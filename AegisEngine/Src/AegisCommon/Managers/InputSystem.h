#pragma once
#ifndef INPUT_SYSTEM_H 
#define INPUT_SYSTEM_H

 //BASURA
#include <vector>
#include<SDL.h>

#include "Singleton.h"
#include "ILuaObject.h"
#include "Vector2.h"

class InputSystem : public Singleton<InputSystem>, public ILuaObject {
private:

	struct key {
		bool wasPressed;
		bool down;
		bool wasReleased;
	};

	struct MouseButton
	{
		key right, left, middle;
	};

	std::vector<key> keys;
	MouseButton mouseButtonState;
	std::pair<Sint32, Sint32> mousePos_;
	int keyNums;
	bool KEY_WAS_PRESSED = false;
	bool KEY_DOWN = false;
	bool KEY_WAS_RELEASED = false;
	Vector2 mouseMotion;

public:
	InputSystem();
	~InputSystem();
	void updateState();
	void clearState();
	int getId(SDL_Keycode key); //keycode

	//UPDATE KEY STATE
	void onKeyDown(SDL_Keycode key);
	void onKeyUp(SDL_Keycode key);
	//UPDATE MOUSE
	void onMouseButtonDown(SDL_MouseButtonEvent buttonEvent);
	void onMouseButtonUp(SDL_MouseButtonEvent buttonEvent);
	void setMouseMotion(Vector2 motion);

	//CONSULT KEY STATE
	bool keyWasPressed(SDL_Keycode key);
	bool isKeyDown(SDL_Keycode key);
	bool keyWasReleased(SDL_Keycode key);
	bool oneKeyWasPressed();
	bool oneKeyIsDown();
	bool oneKeyWasReleased();	
	//CONSULT MOUSE
	bool isMouseButtonDownLua(int button);
	bool isMouseButtonPressedLua(int button);
	bool isMouseButtonReleasedLua(int button);	
	Vector2 getMouseMotion() const;
	Vector2 getMousePosition();

	//For lua
	bool keyWasPressedLua(const char* key);
	bool isKeyDownLua(const char* key);
	bool keyWasReleasedLua(const char* key);
	void blockMouseLua(bool b);

	static void ConvertToLua(lua_State* state);
};


inline InputSystem* Input()
{
	return InputSystem::getInstance();
}

#endif //