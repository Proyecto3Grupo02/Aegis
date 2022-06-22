#include "SceneManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "OgreWrapper.h"

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

	//currentScene = new Scene(ogreWrapper);
	//currentScene->init();
}

SceneManager::~SceneManager() {
	delete currentScene;
	currentScene = nullptr;
}

void SceneManager::loadScene(luabridge::LuaRef scene)
{
	currentScene = new Scene(ogreWrapper);
	currentScene->init();
	//currentScene->free();
	//currentScene->init();
	exportToLua(SceneMngr()->getCurrentScene(), "currentScene");

	luabridge::LuaRef luaUtils = getGlobal(scene.state(), "utils");
	luaUtils["ParseScene"](scene);
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
