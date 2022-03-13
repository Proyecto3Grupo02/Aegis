#pragma once
#ifndef  RENDERER_H 
#define RENDERER_H

#include "ComponentManager.h" //Da error en el cpp
#include "AegisComponent.h" //Da error en el cpp

class OgreWrapper;
class Transform;
class AegisComponent;

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
	Ogre::Entity* getMesh() { return mesh; };

protected:
	void constructoraRenderer(Entity* _ent, std::string meshName, Ogre::SceneManager* sceneMng, bool ir);

	Ogre::SceneNode* node;
	Transform* transform;
	Ogre::Entity* mesh;
};


#endif //RENDERER_H