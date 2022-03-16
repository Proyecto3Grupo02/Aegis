#include "Renderer.h"
#include "../Entity/Entity.h"
//#include "OgreWrapper.h"
#include "Transform.h"

#include "../Utils/Vector3.h"
#include "../Utils/Vector4.h"


void Renderer::render()
{
	Vector3 pos = transform->GetPosition();
	node->setPosition(pos.GetX(), pos.GetY(), pos.GetZ());

	//Resetear la rotación que tenía anteriormente (no existe setRotation)
	Vector4 rot = transform->GetRotation();
	node->setOrientation(Ogre::Quaternion(rot.GetW(), rot.GetX(), rot.GetY(), rot.GetZ()));

	Vector3 scale = transform->GetScale();
	node->setScale(scale.GetX(), scale.GetY(), scale.GetZ());
}

void Renderer::setRendering(bool iR)
{
	node->setVisible(iR);
}

void Renderer::constructoraRenderer(Entity* _ent, std::string meshName, Ogre::SceneManager* sceneMng, bool ir)
{
	setEntity(_ent);
	mesh = sceneMng->createEntity(meshName);
	node = getEntity()->getNode();
	node->attachObject(mesh);

	setRendering(ir);

	transform = getEntity()->getComponent<Transform>();
	if (transform == nullptr) throw "ENTITY WITHOUT TRANSFORM"; //Pulir excepcion
}
