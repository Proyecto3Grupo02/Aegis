#include "AegisMain.h"

//COMPONENTS
#include "AnimationComponent.h"
#include "CameraComponent.h"
#include "LightComponent.h"
#include "RendererComponent.h"
#include "RigidbodyComponent.h"
#include "TransformComponent.h"
#include "SoundEmitterComponent.h"

//MANAGERS
#include "OgreWrapper.h"
#include "InputManager.h"
#include "DebugManager.h"
#include "UISystem.h"
#include "SceneManager.h"
#include "PhysicsMain.h"

//COSAS
#include "Scene.h"
#include "GameLoopData.h"
#include "LuaMaths.h"
#include "Button.h"
#include "Entity.h"
#include "Quaternion.h"

AegisMain::AegisMain() : IInitializable() {
	exit = (false);
	ogreWrap = new OgreWrapper();
	ogreWrap->init();
	LuaMngr();
}

AegisMain::~AegisMain() {
	
	SceneMngr()->deleteInstance(); //me sale error de ejecucion al cerrar si deleteo la escena despues de fisicas
	Physics()->deleteInstance(); //fisicas tiene que hacer delete lo primero o explota
	UIs()->deleteInstance(); //UI tiene que ser delete al principio o explota
	GameTime()->deleteInstance();
	delete ogreWrap;
	Debug()->deleteInstance();
	Input()->deleteInstance();
	Audio()->deleteInstance();	
	LuaMngr()->deleteInstance();
}

void AegisMain::gameLoop() {
	uint32_t frameTimeMS = (uint32_t)floor((1 / TARGET_FRAME_RATE) * 1000);
	//SDL_SetRelativeMouseMode(SDL_TRUE); //comentar para que funcione el boton

	while (!exit)
	{
		SDL_Event eventHandler;
		//Audio()->playMusic("clin"); //Esto hay q quitarlo
		
		//SDL_EnableKeyRepeat(0, 0);
		while (!exit)
		{
			//Tiempo al inicio del frame
			GameTime()->setFrameStartTime(SDL_GetTicks());
			Input()->updateState();
			
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
					Input()->onKeyDown(key);
					break;
				case SDL_KEYUP:
					//std::cout << "KeyUp (" << eventHandler.type << "): ";
					Input()->onKeyUp(key);
					break;
				case SDL_MOUSEBUTTONDOWN:
					Input()->onMouseButtonDown(eventHandler.button);
					break;
				case SDL_MOUSEBUTTONUP:
					Input()->onMouseButtonUp(eventHandler.button);
					break;
				case SDL_MOUSEMOTION:
					// This is usually implemented as a callback but for now it will be this way, just for testing...
					Input()->setMouseMotion(Vector2(eventHandler.motion.xrel, eventHandler.motion.yrel));
					break;
				default:
					//std::cout << "Default (" << eventHandler.type << ")\n";
					break;
				}
			}

			UIs()->update(GameTime()->getDeltaTime()); //boton

			SceneMngr()->updateCurrentScene(GameTime()->getDeltaTime());
			SceneMngr()->preRenderScene();

			ogreWrap->render();
			Uint32 frameTime = SDL_GetTicks() - GameTime()->getFrameStartTime();

			if (frameTime < frameTimeMS)
				SDL_Delay(frameTimeMS - frameTime);

			// Actualiza deltaTime y timeSinceSceneStart
			GameTime()->UpdateTimeRegistry(SDL_GetTicks());
		}
	}
}


/// <summary>
/// Inicializa todos los wrappers (Ogre, Input, Imgui...)
/// </summary>
/// <returns></returns>
bool AegisMain::init()
{
	Debug()->log("Aegis loaded\n");
	std::cout << '\n';
	Input()->init();
	Audio()->init();
	Physics()->init(ogreWrap->getSceneManager());
	UIs()->init(ogreWrap->getSceneManager(), Input());
	convertObjectToLua();
	SceneMngr()->init(new Scene(ogreWrap));
	LuaMngr()->execute("init.lua");

	gameLoop();
	return true;
}

void AegisMain::convertObjectToLua()
{
	auto state = LuaMngr()->getState();

	//MANAGERS
	Scene::ConvertToLua(state);
	InputSystem::ConvertToLua(state);
	SceneManager::ConvertToLua(state);
	UISystem::ConvertToLua(state);
	Entity::ConvertToLua(state);

	//COMPONENTS
	Component::ConvertToLua(state);
	AegisComponent::ConvertToLua(state);
	RendererComponent::ConvertToLua(state);
	LightComponent::ConvertToLua(state);
	CameraComponent::ConvertToLua(state);
	AnimationComponent::ConvertToLua(state);
	RigidbodyComponent::ConvertToLua(state);
	SoundEmitterComponent::ConvertToLua(state);
	TransformComponent::ConvertToLua(state);

	//UTILS
	Vector2::ConvertToLua(state);
	Vector3::ConvertToLua(state);
	Vector4::ConvertToLua(state);
	Quaternion::ConvertToLua(state);
	LuaMaths::ConvertToLua(state);

	exportToLua(UIs(), "UISystem");
	exportToLua(Input(), "Input");
}