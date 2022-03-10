#pragma once
#include "Singleton.h"
#include <vector>
#include<SDL.h>

class InputSystem : public Singleton<InputSystem> {
private:

	struct key {
		bool pressedThisFrame;
		bool down;
		bool releasedThisFrame;
	};
	std::vector<key> keys;
	std::pair<Sint32, Sint32> mousePos_;
	int keyNums;

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
};


inline InputSystem* Input()
{
	return InputSystem::getInstance();
}