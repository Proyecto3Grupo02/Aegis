#include "AegisMain.h"

// COMPONENTS
#include "AnimationComponent.h"
#include "CameraComponent.h"
#include "LightComponent.h"
#include "RendererComponent.h"
#include "RigidbodyComponent.h"
#include "TransformComponent.h"
#include "SoundEmitterComponent.h"

// MANAGERS
#include "OgreWrapper.h"
#include "InputManager.h"
#include "DebugManager.h"
#include "UISystem.h"
#include "SceneManager.h"
#include "PhysicsMain.h"
#include "SoundSystem.h"

// COSAS
#include "Scene.h"
#include "GameLoopData.h"
#include "LuaMaths.h"
#include "Button.h"
#include "Entity.h"
#include "Quaternion.h"

#include "dirent.h"

AegisMain::AegisMain() : IInitializable()
{
	exit = (false);
}

/// <summary>
/// Inicializa todos los wrappers (Ogre, Input, Imgui...)
/// </summary>
/// <returns></returns>
bool AegisMain::init()
{

	GameConfig *config = searchConfig();
	if (config == nullptr)
		return false;

	ogreWrap = new OgreWrapper();
	ogreWrap->init();
	// Audio()->tryCreateInstance();
	SoundSystem::tryCreateInstance();
	PhysicsSystem::tryCreateInstance(ogreWrap->getSceneManager());
	InputSystem::tryCreateInstance();
	UISystem::tryCreateInstance(ogreWrap->getSceneManager(), ogreWrap->getWindowManager(), Input());
	GameLoopData::tryCreateInstance();
	DebugManager::tryCreateInstance();
	SceneManager::tryCreateInstance(ogreWrap);
	LuaManager::tryCreateInstance();

	convertObjectToLua();
	LuaManager::getInstance()->execute("init.lua");

	Debug()->log("Aegis loaded\n");
	std::cout << '\n';

	gameLoop();
	delete config;
	return true;
}

AegisMain::~AegisMain()
{
	free();
}

void AegisMain::free()
{
	SceneManager::tryDeleteInstance();
	PhysicsSystem::tryDeleteInstance();
	UISystem::tryDeleteInstance();
	GameLoopData::tryDeleteInstance();
	delete ogreWrap;
	DebugManager::tryDeleteInstance();
	InputSystem::tryDeleteInstance();
	SoundSystem::tryDeleteInstance();
	LuaManager::tryDeleteInstance();
}

GameConfig *AegisMain::searchConfig()
{
	std::string pathToConfig = searchFile("./", "config.txt");
	if (pathToConfig == "")
	{
		Debug()->log("No config file found\n");
		return nullptr;
	}

	// Open file
	std::ifstream file(pathToConfig);
	if (!file.is_open())
	{
		Debug()->log("Error opening config file\n");
		return nullptr;
	}

	// Read file line by line
	std::string line;

	GameConfig *config = new GameConfig();
	while (std::getline(file, line))
	{
		// Split line by '='
		std::stringstream ss(line);
		std::string key;
		std::string value;
		std::getline(ss, key, '=');
		std::getline(ss, value);

		//Trim end space
		key.erase(std::remove(key.begin(), key.end(), ' '), key.end());

		// Set config value
		if (key == "scripts")
			config->scriptPath = value;
		else if (key == "resources")
			config->resourcesCfgPath = value;
		else if (key == "sounds")
			config->soundsPath = value;
		else
		{
		}
	}

	return config;
}

std::string AegisMain::searchFile(std::string path, std::string file)
{
	// Using dirent, search file in path and subpaths recursively. If it exists return the path, if not return empty string.
	DIR *dir;
	struct dirent *ent;
	std::string pathString = path;
	std::string fileString = file;
	std::string fullPath = "";

	dir = opendir(pathString.c_str());
	if (dir == NULL)
	{
		Debug()->log("Error al abrir el directorio");
		return "";
	}

	while ((ent = readdir(dir)) != nullptr)
	{
		if (ent->d_type == DT_DIR)
		{
			if (strcmp(ent->d_name, ".") != 0 && strcmp(ent->d_name, "..") != 0)
			{
				fullPath = searchFile((pathString + "/" + ent->d_name), fileString);
				if (fullPath != "")
				{
					closedir(dir);
					return fullPath;
				}
			}
		}
		else if (strcmp(ent->d_name, fileString.c_str()) == 0)
		{
			closedir(dir);
			return (pathString + "/" + fileString);
		}
	}
	closedir(dir);

	return "";
}

void AegisMain::gameLoop()
{
	uint32_t frameTimeMS = (uint32_t)floor((1 / TARGET_FRAME_RATE) * 1000);

	while (!exit)
	{
		SDL_Event eventHandler;
		// Audio()->playMusic("clin"); //Esto hay q quitarlo

		// SDL_EnableKeyRepeat(0, 0);
		while (!exit)
		{
			// Tiempo al inicio del frame
			GameTime()->setFrameStartTime(SDL_GetTicks());
			Input()->updateState();

			while (SDL_PollEvent(&eventHandler) != 0)
			{
				ogreWrap->handleEvent(eventHandler);

				auto key = eventHandler.key.keysym.sym;
				switch (eventHandler.type)
				{
				case SDL_QUIT:
					exit = true;
				case SDL_KEYDOWN:
					if (key == SDLK_ESCAPE)
						exit = true;
					// std::cout << "KeyDown (" << eventHandler.type << "): ";
					Input()->onKeyDown(key);
					break;
				case SDL_KEYUP:
					// std::cout << "KeyUp (" << eventHandler.type << "): ";
					Input()->onKeyUp(key);
					break;
				case SDL_MOUSEBUTTONDOWN:
					Input()->onMouseButtonDown(eventHandler.button);
					break;
				case SDL_MOUSEBUTTONUP:
					Input()->onMouseButtonUp(eventHandler.button);
					break;
				case SDL_MOUSEMOTION:
					Input()->setMouseMotion(Vector2(eventHandler.motion.xrel, eventHandler.motion.yrel));
					break;
				default:
					// std::cout << "Default (" << eventHandler.type << ")\n";
					break;
				}
			}

			UIs()->update(GameTime()->getDeltaTime()); // boton

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

void AegisMain::convertObjectToLua()
{
	auto state = LuaMngr()->getState();

	// MANAGERS
	Scene::ConvertToLua(state);
	InputSystem::ConvertToLua(state);
	SceneManager::ConvertToLua(state);
	UISystem::ConvertToLua(state);
	Entity::ConvertToLua(state);

	// COMPONENTS
	Component::ConvertToLua(state);
	AegisComponent::ConvertToLua(state);
	RendererComponent::ConvertToLua(state);
	LightComponent::ConvertToLua(state);
	CameraComponent::ConvertToLua(state);
	AnimationComponent::ConvertToLua(state);
	RigidbodyComponent::ConvertToLua(state);
	SoundEmitterComponent::ConvertToLua(state);
	TransformComponent::ConvertToLua(state);

	// UTILS
	Vector2::ConvertToLua(state);
	Vector3::ConvertToLua(state);
	Vector4::ConvertToLua(state);
	Quaternion::ConvertToLua(state);
	LuaMaths::ConvertToLua(state);

	exportToLua(UIs(), "UISystem");
	exportToLua(Input(), "Input");
}
