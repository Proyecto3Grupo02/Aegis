#include "Renderer.h"
#include "../Entity/Entity.h"
//#include "OgreWrapper.h"

#include "../Utils/MathUtils.h"

using namespace MathUtils;


Renderer::Renderer(Entity* _ent, std::string meshName, std::string matName, Ogre::SceneManager* sceneMng, bool ir) :
	AegisComponent("Renderer", _ent)
{
	isVisible = ir;
	SetDataAsInnerType(this);
	constructoraRenderer(_ent, meshName,matName, sceneMng, ir);
}

Renderer::Renderer(Entity* _ent, std::string meshName, std::string matName) :
	AegisComponent("Renderer", _ent)
{
	isVisible = true;
	SetDataAsInnerType(this);
	constructoraRenderer(_ent, meshName, matName,_ent->getNode()->getCreator(), true);
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

Renderer* CreateRenderer(Entity* _ent, std::string meshName, std::string matName)
{
	return new Renderer(_ent, meshName,matName);
}

void Renderer::constructoraRenderer(Entity* _ent, std::string meshName, std::string matName, Ogre::SceneManager* sceneMng, bool ir)
{
	mesh = sceneMng->createEntity(meshName);
	mesh->setMaterialName(matName);
	std::cout << matName << "\n";
	node = getEntity()->getNode();
	node->attachObject(mesh);
	setRendering(ir);

	transform = getEntity()->GetTransform();
	if (transform == nullptr) throw "ENTITY WITHOUT TRANSFORM"; //Pulir excepcion
}

void Renderer::constructoraRendererLua(Entity* _ent, std::string meshName,std::string matName)
{
	constructoraRenderer(_ent, meshName,matName, _ent->getNode()->getCreator(), isVisible);
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