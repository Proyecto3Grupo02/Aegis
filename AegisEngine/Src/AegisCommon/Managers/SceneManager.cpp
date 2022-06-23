#include "SceneManager.h"
#include "Scene.h"
#include "OgreWrapper.h"
#include "AegisCamera.h"
#include "UISystem.h"

SceneManager::SceneManager(OgreWrapper* ogreWrap)
{
	//LoadScene(sceneName);
	if (ogreWrap)
		this->ogreWrapper = ogreWrap;
	else
	{
		SetInitializationFailed();
		return;
	}

	currentScene = new Scene(ogreWrapper);
}

SceneManager::~SceneManager() {
	if (currentScene)
		delete currentScene;
	currentScene = nullptr;
}

void SceneManager::loadScene(luabridge::LuaRef scene)
{
	this->sceneToLoad = scene;
}

void SceneManager::refresh()
{
	if (!sceneToLoad.isNil())
	{
		currentScene->free();
		currentScene->init();
		UISystem::getInstance()->free();

		luabridge::LuaRef luaUtils = getGlobal(sceneToLoad.state(), "utils");
		luaUtils["ParseScene"](sceneToLoad);
		sceneToLoad = LuaManager::getInstance()->getSharedEmptyLuaRef();
	}
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

void SceneManager::ConvertToLua(lua_State* state)
{
	getGlobalNamespace(state)
		.beginNamespace("Aegis").
		beginClass<SceneManager>("SceneManagerClass").
		addFunction("GetCurrentScene", &SceneManager::getCurrentScene).
		addFunction("LoadScene", &SceneManager::loadScene).
		endClass().
		endNamespace();
}
