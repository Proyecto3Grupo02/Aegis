#include "AegisMain.h"

//OGRE
#include <OgreException.h>
#include <OgreConfigFile.h>
#include <OgreRenderWindow.h>
#include <OgreTextureManager.h>
#include <OgreSceneManager.h>
#include <OgreCamera.h>
#include <OgreViewport.h>
#include <OgreEntity.h>
#include <OgreSceneNode.h>
#include <SDL.h>

#include <iostream>
#include <fstream>

#include "../AegisCommon/Managers/SceneManager.h"
#include "../AegisCommon/Managers/InputManager.h"
#include "../AegisCommon/Managers/DebugManager.h"
#include "../AegisGraphics/OgreWrapper.h"
#include "../AegisScripting/Manager/LuaManager.h"
#include "../AegisCommon/Scene/Scene.h"
#include "../AegisCommon/Utils/GameLoopData.h"
#include "../AegisCommon/Entity/Entity.h"
#include "../AegisCommon/Components/AegisComponent.h"
#include "../AegisCommon/Components/Transform.h"
#include "../AegisCommon/Components/Renderer.h"
#include "../AegisCommon/Utils/Quaternion.h"

using namespace luabridge;

void AegisMain::GameLoop() {
	while (!exit)
	{
		SDL_Event eventHandler;
		uint32_t frameTimeMS = (uint32_t)floor((1 / TARGET_FRAME_RATE) * 1000);
		//Audio()->playMusic("clin");
		std::cout << '\n';
		while (!exit)
		{
			//Tiempo al inicio del frame
			gameLoopData->frameStartTime = SDL_GetTicks();
			Input()->UpdateState();
			while (SDL_PollEvent(&eventHandler) != 0)
			{
				switch (eventHandler.type)
				{
				case SDL_QUIT:
					exit = true;
				case SDL_KEYDOWN:
					if (eventHandler.key.keysym.sym == SDLK_ESCAPE)
						exit = true;
					Input()->OnKeyDown(eventHandler.key.keysym.sym);
					break;
				case SDL_KEYUP:
					Input()->OnKeyUp(eventHandler.key.keysym.sym);
					break;
				default:
					break;
				}
			}

			sceneManager->UpdateCurrentScene(gameLoopData->deltaTime);
			sceneManager->RenderCurrentScene();

			ogreWrap->Render();
			Uint32 frameTime = SDL_GetTicks();

			if (frameTime < frameTimeMS)
				SDL_Delay(frameTimeMS - frameTime);

			// Actualiza deltaTime y timeSinceSceneStart
			gameLoopData->UpdateTimeRegistry(SDL_GetTicks());
		}
	}
}

AegisMain::AegisMain() : IInitializable() {
	luaManager = LuaManager::getInstance();
	ogreWrap = new OgreWrapper();
	ogreWrap->Init();

	gameLoopData = new GameLoopData();
	sceneManager = new SceneManager(new Scene(ogreWrap->GetRootNode()));
	exit = (false);
}

AegisMain::~AegisMain() {
	delete ogreWrap;
	delete sceneManager;
	delete gameLoopData;
}

/// <summary>
/// Inicializa todos los wrappers (Ogre, Input, Imgui...)
/// </summary>
/// <returns></returns>
bool AegisMain::Init()
{
	Debug()->Log("Aegis loaded");
	std::cout << '\n';

	Input()->Init();
	ConvertObjectToLua(); 
	luaManager->Execute("init.lua");
	GameLoop();
	return true;
}

void AegisMain::ConvertObjectToLua()
{
	auto state = luaManager->GetState();

  	Scene::ConvertToLua(state);
	InputSystem::ConvertToLua(state);
	SceneManager::ConvertToLua(state);
	Entity::ConvertToLua(state);
	Component::ConvertToLua(state);
	AegisComponent::ConvertToLua(state);

	Transform::ConvertToLua(state);
	Vector3::ConvertToLua(state);
	Vector4::ConvertToLua(state);
	Quaternion::ConvertToLua(state);
	Renderer::ConvertToLua(state);

	//push(state, true);
	//lua_setglobal(state, "true");
	//
	//push(state, false);
	//lua_setglobal(state, "false");

	push(state, sceneManager->GetCurrentScene());
	lua_setglobal(state, "currentScene");

	push(state, Input());
	lua_setglobal(state, "Input");
}