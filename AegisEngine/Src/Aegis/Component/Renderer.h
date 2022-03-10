#pragma once
#include "AegisComponent.h"

class OgreWrapper;
class Transform;

class Renderer : public AegisComponent {
public:
	Renderer(Entity* _ent, std::string meshName, Ogre::SceneManager* sceneMng, bool ir = true);
	~Renderer() {};
	void render();
	virtual void init(){};
	void setRendering(bool iR);

protected:
	Ogre::SceneNode* node;
	Transform* transform;
	Ogre::Entity* mesh;
};