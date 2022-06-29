#include "SkyboxComponent.h"
#include "Entity.h"

#include "MathUtils.h"

SkyboxComponent::SkyboxComponent(Entity* _ent, std::string meshName, std::string matName, Ogre::SceneManager* sceneMng, bool ir) :
	AegisComponent("Skybox", _ent)
{
	isVisible = ir;
	setDataAsInnerType(this);
	constructoraSkybox(_ent, meshName, matName, sceneMng, isVisible);
}

SkyboxComponent::SkyboxComponent(Entity* _ent, std::string meshName, std::string matName) :
	AegisComponent("Skybox", _ent)
{
	isVisible = true;
	setDataAsInnerType(this);
	constructoraSkybox(_ent, meshName, matName, _ent->getNode()->getCreator(), isVisible);
}

SkyboxComponent::SkyboxComponent()
{
	isVisible = true;
	setDataAsInnerType(this);
	setComponentName("Skybox");
}

void SkyboxComponent::constructoraSkybox(Entity* _ent, std::string meshName, std::string matName, Ogre::SceneManager* sceneMng, bool ir)
{
	sceneMng->setSkyBox(true, meshName);
	//sceneMng->setSkyPlane(true, Ogre::Plane(Ogre::Vector3(0, 0, 1), -100), meshName, 1, 1, true, 1, 10, 10);
	mesh = sceneMng->createEntity(meshName);
	mesh->setMaterialName(matName);

	node = getEntity()->getNode();
	node->attachObject(mesh);
	setRendering(ir);

	transform = getEntity()->getTransform();
	if (transform == nullptr) throw "ENTITY WITHOUT TRANSFORM"; //Pulir excepcion
}

void SkyboxComponent::constructoraSkyboxLua(Entity* _ent, std::string meshName, std::string matName)
{
	constructoraSkybox(_ent, meshName, matName, _ent->getNode()->getCreator(), isVisible);
}

SkyboxComponent* CreateSkybox(Entity* _ent, std::string meshName, std::string matName)
{
	return new SkyboxComponent(_ent, meshName, matName);
}

void SkyboxComponent::ConvertToLua(lua_State* state)
{
	getGlobalNamespace(state).
		beginNamespace("Aegis").
		beginNamespace("NativeComponents").
		addFunction("CreateSkybox", CreateSkybox).
		deriveClass<SkyboxComponent, AegisComponent>("Skybox").
		addProperty("visible", &SkyboxComponent::getRendering, &SkyboxComponent::setRendering).
		endClass().
		endNamespace().
		endNamespace();
}