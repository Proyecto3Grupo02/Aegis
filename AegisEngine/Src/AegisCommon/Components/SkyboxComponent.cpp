#include "SkyboxComponent.h"
#include "Entity.h"

#include "MathUtils.h"

SkyboxComponent::SkyboxComponent(Entity* _ent, std::string matName, Ogre::SceneManager* sceneMng, bool ir) :
	AegisComponent("Skybox", _ent)
{
	isVisible = ir;
	setDataAsInnerType(this);
	constructoraSkybox(_ent, matName, sceneMng, isVisible);
}

SkyboxComponent::SkyboxComponent(Entity* _ent, std::string matName) :
	AegisComponent("Skybox", _ent)
{
	isVisible = true;
	setDataAsInnerType(this);
	constructoraSkybox(_ent, matName, _ent->getNode()->getCreator(), isVisible);
}

SkyboxComponent::SkyboxComponent()
{
	isVisible = true;
	setDataAsInnerType(this);
	setComponentName("Skybox");
}

void SkyboxComponent::constructoraSkybox(Entity* _ent, std::string matName, Ogre::SceneManager* sceneMng, bool ir)
{
	// Mesh se separa de Entity para la gestion del ssistema,d ado que la mesh no se va a cargar, sino crear
	mesh = new Ogre::Plane(Ogre::Vector3(0, 0, 1), -100);
	sceneMng->setSkyPlane(true,*mesh , matName, 1, 1, true, 1, 10, 10);
	entity = sceneMng->createEntity(_ent->getName() + " " + matName);
	entity->setMaterialName(matName);

	node = getEntity()->getNode();
	node->attachObject(entity);
	setRendering(ir);

	transform = getEntity()->getTransform(); //como transform es un componente nativo, no es necesario comprobar si es null
}

void SkyboxComponent::constructoraSkyboxLua(Entity* _ent, std::string matName)
{
	constructoraSkybox(_ent, matName, _ent->getNode()->getCreator(), isVisible);
}

SkyboxComponent* CreateSkybox(Entity* _ent, std::string matName)
{
	return new SkyboxComponent(_ent, matName);
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