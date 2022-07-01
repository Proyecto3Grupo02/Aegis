#include "SkyboxComponent.h"
#include "Entity.h"

#include "MathUtils.h"

SkyboxComponent::SkyboxComponent(Entity* _ent, std::string matName, bool ir) :
	AegisComponent("Skybox", _ent)
{
	isVisible = ir;
	setDataAsInnerType(this);
	constructoraSkybox(_ent, matName, isVisible);
}

SkyboxComponent::SkyboxComponent(Entity* _ent, std::string matName) :
	AegisComponent("Skybox", _ent)
{
	isVisible = true;
	constructoraSkybox(_ent, matName, isVisible);
	setDataAsInnerType(this);
}

SkyboxComponent::SkyboxComponent()
{
	isVisible = true;
	setDataAsInnerType(this);
	setComponentName("Skybox");
}

void SkyboxComponent::constructoraSkybox(Entity* _ent, std::string matName, bool ir)
{
	_ent->getNode()->getCreator()->setSkyBox(true,matName);
}

void SkyboxComponent::constructoraSkyboxLua(Entity* _ent, std::string matName)
{
	constructoraSkybox(_ent, matName, isVisible);
}

SkyboxComponent* CreateSkybox(Entity* _ent, std::string matName)
{
	return new SkyboxComponent(_ent, matName,true);
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