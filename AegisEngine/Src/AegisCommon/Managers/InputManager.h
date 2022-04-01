#pragma once
#ifndef INPUT_SYSTEM_H 
#define INPUT_SYSTEM_H

#include "../Utils/Singleton.h"
#include <vector>
#include<SDL.h>
#include "../Interfaces/ILuaObject.h"

class InputSystem : public Singleton<InputSystem>, public ILuaObject {
private:

	struct key {
		bool pressedThisFrame;
		bool down;
		bool releasedThisFrame;
	};
	std::vector<key> keys;
	std::pair<Sint32, Sint32> mousePos_;
	int keyNums;
	bool keydown = false;
	bool keyup = false;
	bool keypressed = false;
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
	bool isKeyUp(SDL_Keycode key);
	bool isKeyDown(SDL_Keycode key);
	bool isKeyPressedThisFrame(SDL_Keycode key);
	bool isAnyKeyDown();
	bool isAnyKeyUp();
	bool isAnyKeyPressed();

	//For lua
	bool isKeyUpLua(const char* key);
	bool isKeyDownLua(const char* key);
	bool isKeyPressedThisFrameLua(const char* key);

	static void ConvertToLua(lua_State* state);
};


inline InputSystem* Input()
{
	return InputSystem::getInstance();
}

#endif //