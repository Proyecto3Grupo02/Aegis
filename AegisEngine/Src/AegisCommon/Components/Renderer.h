#pragma once
#ifndef  RENDERER_H 
#define RENDERER_H

#include "../Managers/ComponentManager.h" //Da error en el cpp
#include "AegisComponent.h" //Da error en el cpp
#include "../../checkML.h" //BASURA

class OgreWrapper;
class Transform;
class AegisComponent;

class Renderer : public AegisComponent {
public:
	Renderer(Entity* _ent, std::string meshName, std::string materialName, Ogre::SceneManager* sceneMng, bool ir = true): AegisComponent() {
		ComponentManager::getInstance()->RegisterComponent<Renderer>("Renderer");
		constructoraRenderer(_ent, meshName, sceneMng, ir);
		setMaterialName(materialName);
	}

	~Renderer() {};

	virtual void init(){};
	void setRendering(bool iR);
	Ogre::Entity* getMesh() { return mesh; };
	void setMaterialName(std::string name) {
		mesh->setMaterialName(name);
	}
protected:
	void constructoraRenderer(Entity* _ent, std::string meshName, Ogre::SceneManager* sceneMng, bool ir);

	Ogre::SceneNode* node;
	Transform* transform;
	Ogre::Entity* mesh;
};


#endif //RENDERER_H