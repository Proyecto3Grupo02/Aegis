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

void SceneManager::loadScene(std::string sceneName)
{
	//currentScene = new Scene();
}

void SceneManager::updateCurrentScene(float deltaTime) {
	currentScene->updateScene(deltaTime);
}

void SceneManager::preRenderScene() {
	currentScene->render();
}

Scene* SceneManager::getCurrentScene()
{
	return currentScene;
}

void SceneManager::changeScene(std::string sceneName)
{
	delete currentScene;
	loadScene(sceneName);
}

void SceneManager::ConvertToLua(lua_State* state)
{
	getGlobalNamespace(state).beginNamespace("Aegis").endNamespace();
}
