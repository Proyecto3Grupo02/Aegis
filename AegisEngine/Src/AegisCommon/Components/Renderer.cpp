#include "Renderer.h"
#include "../Entity/Entity.h"
//#include "OgreWrapper.h"
#include "Transform.h"

#include "../Utils/Vector3.h"
#include "../Utils/Vector4.h"


void Renderer::setRendering(bool iR)
{
	node->setVisible(iR);
}

void Renderer::constructoraRenderer(Entity* _ent, std::string meshName, Ogre::SceneManager* sceneMng, bool ir)
{
	setEntity(_ent);
	node = getEntity()->getNode();
	node->attachObject(mesh);
	mesh = sceneMng->createEntity(meshName);
	setRendering(ir);
	transform = getEntity()->getComponent<Transform>();
	
	assert(transform != nullptr);
}
