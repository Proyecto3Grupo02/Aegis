#pragma once
#include "AegisComponent.h"

class OgreWrapper;
class Transform;

class Renderer : public AegisComponent {
public:
	Renderer(Entity* _ent, std::string meshName, Ogre::SceneManager* sceneMng, bool ir = true);
	~Renderer() {};
	void render();

	void setRendering(bool iR);

protected:
	Vector4 previousRotation;
	Ogre::SceneNode* node;
	Transform* transform;
	Ogre::Entity* mesh;
};