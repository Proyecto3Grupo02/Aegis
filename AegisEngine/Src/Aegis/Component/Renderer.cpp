#include "Renderer.h"
#include "Entity.h"
#include "OgreWrapper.h"
#include "Transform.h"

Renderer::Renderer(Entity* _ent, std::string meshName, Ogre::SceneManager* sceneMng, bool ir = true) : 
	AegisComponent(_ent), previousRotation(Vector4())
{
	setRendering(ir);
	mesh = sceneMng->createEntity(meshName);
	node = getEntity()->getNode();
	node->attachObject(mesh);

	transform = getEntity()->getComponent<Transform>();
	if (transform == nullptr) throw "ENTITY WITHOUT TRANSFORM"; //Pulir excepcion
}

void Renderer::render()
{
	Vector3 pos = transform->GetPosition();
	node->setPosition(pos.GetX(), pos.GetY(), pos.GetZ());

	//Resetear la rotación que tenía anteriormente (no existe setRotation)
	node->rotate(Ogre::Quaternion(-previousRotation.GetW(), -previousRotation.GetX(), -previousRotation.GetY(), -previousRotation.GetZ()));

	Vector4 rot = transform->GetRotation();
	node->rotate(Ogre::Quaternion(rot.GetW(), rot.GetX(), rot.GetY(), rot.GetZ()));

	Vector3 scale = transform->GetScale();
	node->setScale(scale.GetX(), scale.GetY(), scale.GetZ());



	previousRotation = rot;
}

void Renderer::setRendering(bool iR)
{
	mesh->setVisible(iR);
}
