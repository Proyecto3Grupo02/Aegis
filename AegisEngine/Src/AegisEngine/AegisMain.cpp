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
#include "../AegisPhysics/PhysicsMain.h"
#include "../AegisCommon/Scene/Scene.h"
#include "../AegisCommon/Utils/GameLoopData.h"
#include "../AegisCommon/Entity/Entity.h"
#include "../AegisCommon/Components/AegisComponent.h"
#include "../AegisCommon/Components/Transform.h"
#include "../AegisCommon/Components/Renderer.h"
#include "../AegisCommon/Utils/Quaternion.h"
#include "../AegisAudio/SoundSystem.h"
#include "../AegisCommon/Components/LightComponent.h"
#include "../AegisCommon/Components/CameraComponent.h"
#include "../AegisCommon/Components/AnimationComponent.h"
#include "../AegisCommon/Components/RigidbodyComponent.h"
#include "../AegisCommon/Utils/Vector2.h"
#include "../AegisCommon/Components/SoundEmitterComponent.h"

//using namespace luabridge;

void AegisMain::GameLoop() {

	uint32_t frameTimeMS = (uint32_t)floor((1 / TARGET_FRAME_RATE) * 1000);
	SDL_SetRelativeMouseMode(SDL_TRUE);

	while (!exit)
	{
		SDL_Event eventHandler;

		
		//SDL_EnableKeyRepeat(0, 0);
		while (!exit)
		{
			//Tiempo al inicio del frame
			gameLoopData->frameStartTime = SDL_GetTicks();
			Input()->UpdateState();
			while (SDL_PollEvent(&eventHandler) != 0)
			{
				auto key = eventHandler.key.keysym.sym;
				switch (eventHandler.type)
				{
				case SDL_QUIT:
					exit = true;
				case SDL_KEYDOWN:
					if (key == SDLK_ESCAPE)
						exit = true;
					//std::cout << "KeyDown (" << eventHandler.type << "): ";
					Input()->OnKeyDown(key);
					break;
				case SDL_KEYUP:
					//std::cout << "KeyUp (" << eventHandler.type << "): ";
					Input()->OnKeyUp(key);
					break;
				case SDL_MOUSEMOTION:
					// This is usually implemented as a callback but for now it will be this way, just for testing...
					Input()->SetMouseMotion(Vector2(eventHandler.motion.xrel, eventHandler.motion.yrel));
					break;
				default:
					//std::cout << "Default (" << eventHandler.type << ")\n";
					break;
				}
			}

			sceneManager->UpdateCurrentScene(gameLoopData->deltaTime);
			sceneManager->PreRenderScene();

			ogreWrap->Render();
			Uint32 frameTime = SDL_GetTicks() - gameLoopData->frameStartTime;

			if (frameTime < frameTimeMS)
				SDL_Delay(frameTimeMS - frameTime);

			// Actualiza deltaTime y timeSinceSceneStart
			gameLoopData->UpdateTimeRegistry(SDL_GetTicks());
		}
	}
}

AegisMain::AegisMain() : IInitializable() {
	exit = (false);
	ogreWrap = new OgreWrapper();
	ogreWrap->Init();
	LuaMngr();

	gameLoopData = new GameLoopData();
	sceneManager = new SceneManager(new Scene(ogreWrap));
}

AegisMain::~AegisMain() {
	delete gameLoopData;
	delete sceneManager;
	delete ogreWrap;

	Debug()->deleteInstance();
	Input()->deleteInstance();
	Audio()->close();
	Audio()->deleteInstance();
	Physics()->remove();
	Physics()->deleteInstance();
	LuaMngr()->deleteInstance();
}

/// <summary>
/// Inicializa todos los wrappers (Ogre, Input, Imgui...)
/// </summary>
/// <returns></returns>
bool AegisMain::Init()
{
	Debug()->Log("Aegis loaded\n");
	std::cout << '\n';

	Input()->Init();
	Audio()->Init();
	Physics()->Init();
	ConvertObjectToLua();
	sceneManager->GetCurrentScene()->Init();
	LuaMngr()->Execute("init.lua");
	GameLoop();
	return true;
}

void AegisMain::ConvertObjectToLua()
{
	auto state = LuaMngr()->GetState();

	Scene::ConvertToLua(state);
	InputSystem::ConvertToLua(state);
	SceneManager::ConvertToLua(state);
	Entity::ConvertToLua(state);
	Component::ConvertToLua(state);
	AegisComponent::ConvertToLua(state);

	Transform::ConvertToLua(state);
	Vector2::ConvertToLua(state);
	Vector3::ConvertToLua(state);
	Vector4::ConvertToLua(state);
	Quaternion::ConvertToLua(state);
	Renderer::ConvertToLua(state);
	LightComponent::ConvertToLua(state);
	CameraComponent::ConvertToLua(state);
	AnimationComponent::ConvertToLua(state);
	RigidbodyComponent::ConvertToLua(state);
	//MathUtils::ConvertToLua(state);
	SoundEmitterComponent::ConvertToLua(state);

	ExportToLua(sceneManager->GetCurrentScene(), "currentScene");
	ExportToLua(Input(), "Input");
}