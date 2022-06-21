#pragma once
#ifndef SCENE_MANAGER_H 
#define SCENE_MANAGER_H

#include <string>
#include "ILuaObject.h"
#include <Singleton.h>

class Scene;

class SceneManager : public Singleton<SceneManager>, public ILuaObject
{
private:
	Scene* currentScene;
	void loadScene(std::string sceneName);

public:
	SceneManager();
	~SceneManager();

	void init(Scene* scene);
	void updateCurrentScene(float deltaTime);
	void preRenderScene();
	void changeScene(std::string sceneName);
	Scene* getCurrentScene();
	static void ConvertToLua(lua_State* state);
};

inline SceneManager* SceneMngr()
{
	return SceneManager::getInstance();
}

#endif