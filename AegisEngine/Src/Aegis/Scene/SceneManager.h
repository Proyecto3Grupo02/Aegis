#pragma once
#ifndef SCENE_MANAGER_H 
#define SCENE_MANAGER_H

#include <string>

namespace AegisEngine {
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
}
#endif