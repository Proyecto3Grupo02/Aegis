#pragma once
#ifndef SCENE_MANAGER_H 
#define SCENE_MANAGER_H

#include <string>
#include "ILuaObject.h"

class Scene;

class SceneManager : public ILuaObject
{
private:
	Scene* currentScene;
	void LoadScene(std::string sceneName);

public:
	SceneManager(Scene* scene);
	~SceneManager();

	void UpdateCurrentScene(float deltaTime);
	void PreRenderScene();
	void ChangeScene(std::string sceneName);
	Scene* GetCurrentScene();
	static void ConvertToLua(lua_State* state);
};
#endif