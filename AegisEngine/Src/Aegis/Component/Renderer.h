#pragma once
#include "AegisComponent.h"
#include "ComponentManager.h"

class OgreWrapper;
class Transform;

class Renderer : public AegisComponent {
public:
	Renderer(Entity* _ent, std::string meshName, Ogre::SceneManager* sceneMng, bool ir = true):
		AegisComponent()
	{
		ComponentManager::getInstance()->RegisterComponent<Renderer>("Renderer");
		constructoraRenderer(_ent, meshName, sceneMng, ir);
	}

	~Renderer() {};

	void render();
	virtual void init(){};
	void setRendering(bool iR);
	Ogre::Entity* getMesh() { return mesh; }

protected:
	void constructoraRenderer(Entity* _ent, std::string meshName, Ogre::SceneManager* sceneMng, bool ir);

	Ogre::SceneNode* node;
	Transform* transform;
	Ogre::Entity* mesh;
};