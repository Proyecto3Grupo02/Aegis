#include "Renderer.h"
#include "../Entity/Entity.h"
//#include "OgreWrapper.h"
#include "Transform.h"

#include "../Utils/Vector3.h"
#include "../Utils/Vector4.h"

Renderer::Renderer(Entity* _ent, std::string meshName, std::string materialName, Ogre::SceneManager* sceneMng, bool ir): AegisComponent() {
	ComponentManager::getInstance()->RegisterComponent<Renderer>("Renderer");
	constructoraRenderer(_ent, meshName, sceneMng, ir);
	setMaterialName(materialName);
}

Renderer::~Renderer(){}

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
