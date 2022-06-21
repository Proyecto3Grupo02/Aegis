#include "SceneManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "OgreWrapper.h"

SceneManager::SceneManager(OgreWrapper* ogreWrap)
{
	//LoadScene(sceneName);
	this->ogreWrapper = ogreWrap;
}

SceneManager::~SceneManager() {
	delete currentScene;
	currentScene = nullptr;
}

void SceneManager::loadScene(luabridge::LuaRef scene)
{
	currentScene = new Scene(ogreWrapper);
	currentScene->init();
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

	exportToLua(SceneManager::getInstance(), "SceneManager");
}
