#include "SceneManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "OgreWrapper.h"

SceneManager::SceneManager(OgreWrapper* ogreWrap)
{
	//LoadScene(sceneName);
	currentScene = new Scene(ogreWrap);
	currentScene->init();
	exportToLua(SceneMngr()->getCurrentScene(), "currentScene");
}

SceneManager::~SceneManager() {
	delete currentScene;
	currentScene = nullptr;
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
