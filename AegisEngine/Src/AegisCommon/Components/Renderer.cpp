#include "Renderer.h"
#include "../Entity/Entity.h"
//#include "OgreWrapper.h"
#include "Transform.h"

#include "../Utils/Vector3.h"
#include "../Utils/Vector4.h"


Renderer::Renderer(Entity* _ent, std::string meshName, Ogre::SceneManager* sceneMng, bool ir) :
	AegisComponent("Renderer", _ent)
{
	data["mesh"] = "fish.mesh";
	isVisible = ir;
	SetDataAsInnerType(this);
	constructoraRenderer(_ent, meshName, sceneMng, ir);
}

Renderer::Renderer(Entity* _ent, std::string meshName) :
	AegisComponent("Renderer", _ent)
{
	data["mesh"] = "fish.mesh";
	isVisible = true;
	SetDataAsInnerType(this);
	constructoraRenderer(_ent, meshName, _ent->getNode()->getCreator(), true);
}

Renderer::Renderer()
{
	isVisible = true;
	SetDataAsInnerType(this);
	SetComponentName("Renderer");
}

void Renderer::render()
{

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

void Renderer::constructoraRenderer(Entity* _ent, std::string meshName, Ogre::SceneManager* sceneMng, bool ir)
{
	mesh = sceneMng->createEntity(meshName);
	node = getEntity()->getNode();
	node->attachObject(mesh);
	mesh = sceneMng->createEntity(meshName);
	setRendering(ir);

	transform = getEntity()->GetTransform();
	if (transform == nullptr) throw "ENTITY WITHOUT TRANSFORM"; //Pulir excepcion
}

void Renderer::constructoraRendererLua(Entity* _ent, std::string meshName)
{
	constructoraRenderer(_ent, meshName, _ent->getNode()->getCreator(), isVisible);
}

void Renderer::ConvertToLua(lua_State* state)
{
	getGlobalNamespace(state).
		beginNamespace("Aegis").
		beginNamespace("NativeComponents").
		addFunction("CreateRenderer", CreateRenderer).
		deriveClass<Renderer, AegisComponent>("Renderer").
		addProperty("visible", &Renderer::getRendering, &Renderer::setRendering).
		endClass().
		endNamespace().
		endNamespace();
}