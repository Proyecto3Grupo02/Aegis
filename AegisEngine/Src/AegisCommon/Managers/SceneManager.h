#pragma once
#ifndef SCENE_MANAGER_H 
#define SCENE_MANAGER_H

#include <string>
#include "ILuaObject.h"
#include <Singleton.h>

class Scene;
class OgreWrapper;

class SceneManager : public Singleton<SceneManager>, public ILuaObject
{
private:
	Scene* currentScene = nullptr;
	OgreWrapper* ogreWrapper = nullptr;
	void loadScene(luabridge::LuaRef scene);

public:
	SceneManager(OgreWrapper* ogreWrap);
	~SceneManager();

	void updateCurrentScene(float deltaTime);
	void preRenderScene();
	Scene* getCurrentScene();
	static void ConvertToLua(lua_State* state);
};
#endif