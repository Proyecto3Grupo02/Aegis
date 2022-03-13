#pragma once
#include <string>

class Scene;

class SceneManager
{
private:
	Scene* currentScene;
	void LoadScene(std::string sceneName);
public:
	SceneManager(std::string sceneName);
	~SceneManager();

	void UpdateCurrentScene(float deltaTime);
	void RenderCurrentScene();
	void ChangeScene(std::string sceneName);
};