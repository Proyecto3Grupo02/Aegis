#include "AegisMain.h"

//OGRE
#include "../AegisCommon/Components/AnimationComponent.h"
#include "../AegisCommon/Components/CameraComponent.h"
#include "../AegisCommon/Components/LightComponent.h"
#include "../AegisCommon/Components/Renderer.h"
#include "../AegisCommon/Components/RigidbodyComponent.h"
#include "../AegisCommon/Entity/Entity.h"
#include "../AegisCommon/Managers/InputManager.h"
#include "../AegisCommon/Managers/SceneManager.h"
#include "../AegisCommon/Managers/DebugManager.h"
#include "../AegisCommon/Scene/Scene.h"
#include "../AegisGraphics/OgreWrapper.h"
#include "../AegisPhysics/PhysicsMain.h"
#include "../AegisCommon/Components/Transform.h"
#include "GameLoopData.h"
#include "LuaMaths.h"
#include "../AegisCommon/Components/SoundEmitterComponent.h"

#include "../AegisUI/UIMain.h"

using namespace luabridge;

void AegisMain::GameLoop() {
	uint32_t frameTimeMS = (uint32_t)floor((1 / TARGET_FRAME_RATE) * 1000);
	SDL_SetRelativeMouseMode(SDL_TRUE);

	while (!exit)
	{
		SDL_Event eventHandler;

		//Audio()->playMusic("clin"); //Esto hay q quitarlo
		
		//SDL_EnableKeyRepeat(0, 0);
		while (!exit)
		{
			//Tiempo al inicio del frame
			Time()->frameStartTime = SDL_GetTicks();
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
				case SDL_MOUSEBUTTONDOWN:
					Input()->OnMouseButtonDown(eventHandler.button);
					break;
				case SDL_MOUSEBUTTONUP:
					Input()->OnMouseButtonUp(eventHandler.button);
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

			sceneManager->UpdateCurrentScene(Time()->deltaTime);
			sceneManager->PreRenderScene();

			ogreWrap->Render();
			//El renderizado de la UI se superpone ahora mismo al del gameplay
			//hay que comprobar los buffers
			//UIs()->Render();
			sceneManager->RenderUI();
			Uint32 frameTime = SDL_GetTicks() - Time()->frameStartTime;

			if (frameTime < frameTimeMS)
				SDL_Delay(frameTimeMS - frameTime);

			// Actualiza deltaTime y timeSinceSceneStart
			Time()->UpdateTimeRegistry(SDL_GetTicks());
		}
	}
}

AegisMain::AegisMain() : IInitializable() {
	exit = (false);
	ogreWrap = new OgreWrapper();
	ogreWrap->Init();
	LuaMngr();

	gameLoopData = new TimeManager();
	sceneManager = new SceneManager(new Scene(ogreWrap));
}

AegisMain::~AegisMain() {
	delete Time();
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
	UIs()->Init(ogreWrap->getSceneManager());
	ConvertObjectToLua();
	sceneManager->GetCurrentScene()->Init();
	LuaMngr()->Execute("init.lua");

	UIs()->CreateUIImage("ramon", 0, "grass");
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
	SoundEmitterComponent::ConvertToLua(state);
	LuaMaths::ConvertToLua(state);

	ExportToLua(sceneManager->GetCurrentScene(), "currentScene");
	ExportToLua(Input(), "Input");
}