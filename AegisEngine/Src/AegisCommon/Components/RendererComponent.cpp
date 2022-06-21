#include "RendererComponent.h"
#include "Entity.h"
//#include "OgreWrapper.h"

#include "MathUtils.h"

RendererComponent::RendererComponent(Entity* _ent, std::string meshName, std::string matName, Ogre::SceneManager* sceneMng, bool ir) :
	AegisComponent("Renderer", _ent)
{
	isVisible = ir;
	setDataAsInnerType(this);
	constructoraRenderer(_ent, meshName,matName, sceneMng, ir);
}

RendererComponent::RendererComponent(Entity* _ent, std::string meshName, std::string matName) :
	AegisComponent("Renderer", _ent)
{
	isVisible = true;
	setDataAsInnerType(this);
	constructoraRenderer(_ent, meshName, matName,_ent->getNode()->getCreator(), true);
}

RendererComponent::RendererComponent()
{
	isVisible = true;
	setDataAsInnerType(this);
	setComponentName("Renderer");
}

void RendererComponent::render()
{

}

void RendererComponent::setRendering(bool iR)
{
	isVisible = iR;
	node->setVisible(iR);
}

bool RendererComponent::getRendering() const
{
	return isVisible;
}

RendererComponent* CreateRenderer(Entity* _ent, std::string meshName, std::string matName)
{
	return new RendererComponent(_ent, meshName,matName);
}

void RendererComponent::constructoraRenderer(Entity* _ent, std::string meshName, std::string matName, Ogre::SceneManager* sceneMng, bool ir)
{
	mesh = sceneMng->createEntity(meshName);
	mesh->setMaterialName(matName);
	//std::cout << matName << "\n";
	node = getEntity()->getNode();
	node->attachObject(mesh);
	setRendering(ir);

	transform = getEntity()->getTransform();
	if (transform == nullptr) throw "ENTITY WITHOUT TRANSFORM"; //Pulir excepcion
}

void RendererComponent::constructoraRendererLua(Entity* _ent, std::string meshName,std::string matName)
{
	constructoraRenderer(_ent, meshName,matName, _ent->getNode()->getCreator(), isVisible);
}

void RendererComponent::ConvertToLua(lua_State* state)
{
	getGlobalNamespace(state).
			beginNamespace("Aegis").
				beginNamespace("NativeComponents").
				addFunction("CreateRenderer", CreateRenderer).
				deriveClass<RendererComponent, AegisComponent>("Renderer").
				addProperty("visible", &RendererComponent::getRendering, &RendererComponent::setRendering).
				endClass().
			endNamespace().
		endNamespace();
}