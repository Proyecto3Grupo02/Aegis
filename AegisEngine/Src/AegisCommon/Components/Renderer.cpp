#include "Renderer.h"
#include "../Entity/Entity.h"
//#include "OgreWrapper.h"
#include "Transform.h"

#include "../Utils/Vector3.h"
#include "../Utils/Vector4.h"


Renderer::Renderer(Entity* _ent, std::string meshName) :
	AegisComponent()
{
	isVisible = true;
	SetComponentName("Renderer");
	//ComponentManager::getInstance()->RegisterComponent<Renderer>("Renderer");
	constructoraRenderer(_ent, meshName, _ent->GetNode()->getCreator(), true);
}

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
	isVisible = iR;
	node->setVisible(iR);
}

bool Renderer::getRendering() const
{
	return isVisible;
}

Renderer* CreateRenderer(Entity* _ent, std::string meshName)
{
	return new Renderer(_ent, meshName);
}

void Renderer::ConvertToLua(lua_State* state)
{
	getGlobalNamespace(state).
		beginNamespace("ECS").
		addFunction("CreateRenderer", CreateRenderer).
		deriveClass<Renderer, AegisComponent>("Renderer").
		addProperty("visible", &Renderer::getRendering, &Renderer::setRendering).
		endClass().
		endNamespace();
}

void Renderer::constructoraRenderer(Entity* _ent, std::string meshName, Ogre::SceneManager* sceneMng, bool ir)
{
	setEntity(_ent);
	mesh = sceneMng->createEntity(meshName);
	node = getEntity()->getNode();
	node->attachObject(mesh);

	setRendering(ir);

	transform = getEntity()->GetTransform();
	if (transform == nullptr) throw "ENTITY WITHOUT TRANSFORM"; //Pulir excepcion
}
