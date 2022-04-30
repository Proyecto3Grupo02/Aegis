#pragma once
#ifndef INPUT_SYSTEM_H 
#define INPUT_SYSTEM_H

#include "../Utils/Singleton.h"
 //BASURA
#include <vector>
#include<SDL.h>
#include "../Interfaces/ILuaObject.h"
#include "../Utils/Vector2.h"

class InputSystem : public Singleton<InputSystem>, public ILuaObject {
private:

	struct key {
		bool wasPressed;
		bool down;
		bool wasReleased;
	};
	std::vector<key> keys;
	std::pair<Sint32, Sint32> mousePos_;
	int keyNums;
	bool KEY_WAS_PRESSED = false;
	bool KEY_DOWN = false;
	bool KEY_WAS_RELEASED = false;
	Vector2 mouseMotion;
public:

	InputSystem();
	~InputSystem();
	void Init();
	void UpdateState();
	void ClearState();
	int getId(SDL_Keycode key); //keycode

	//UPDATE KEY STATE
	void OnKeyDown(SDL_Keycode key);
	void OnKeyUp(SDL_Keycode key);

	//CONSULT KEY STATE
	bool keyWasPressed(SDL_Keycode key);
	bool isKeyDown(SDL_Keycode key);
	bool keyWasReleased(SDL_Keycode key);
	
	bool oneKeyWasPressed();
	bool oneKeyIsDown();
	bool oneKeyWasReleased();	

	//For lua
	bool keyWasPressedLua(const char* key);
	bool isKeyDownLua(const char* key);
	bool keyWasReleasedLua(const char* key);

	static void ConvertToLua(lua_State* state);

	void SetMouseMotion(Vector2 motion);
	Vector2 GetMouseMotion() const;

	Vector2 getMousePosition() const;
};


inline InputSystem* Input()
{
	return InputSystem::getInstance();
}

#endif //