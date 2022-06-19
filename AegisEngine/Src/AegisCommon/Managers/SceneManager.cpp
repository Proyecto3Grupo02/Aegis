#include "SceneManager.h"
#include "Scene.h"

SceneManager::SceneManager(Scene* scene)
{
	//LoadScene(sceneName);
	currentScene = scene;
}

SceneManager::~SceneManager() {
	delete currentScene;
}

void SceneManager::LoadScene(std::string sceneName)
{
	//currentScene = new Scene();
}

void SceneManager::UpdateCurrentScene(float deltaTime) {
	currentScene->UpdateScene(deltaTime);
}

void SceneManager::PreRenderScene() {
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
	getGlobalNamespace(state).beginNamespace("Aegis").endNamespace();
}
