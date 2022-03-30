#include "SceneManager.h"
#include "Scene.h"

SceneManager::SceneManager(std::string sceneName)
{
	LoadScene(sceneName);
}

SceneManager::~SceneManager()
{
	delete currentScene;
}

void SceneManager::LoadScene(std::string sceneName)
{
	currentScene = new Scene();
}

void SceneManager::UpdateCurrentScene(float deltaTime)
{
	currentScene->UpdateScene(deltaTime);
}

void SceneManager::RenderCurrentScene()
{
	currentScene->Render();
}

Scene* SceneManager::GetCurrentScene()
{
	return currentScene;
}

void SceneManager::ChangeScene(std::string sceneName)
{
	delete currentScene;
	LoadScene(sceneName);
}

void SceneManager::ConvertToLua(lua_State* state)
{
	getGlobalNamespace(state).beginNamespace("ECS").endNamespace();
}
