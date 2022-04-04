#include "LightComponent.h"
#include "../Entity/Entity.h"

void LightComponent::initLight()
{
	mLight_ = new AegisLight(getEntity()->getNode(),getEntity()->getNode()->getCreator());
}

LightComponent::LightComponent(Entity* ent,LuaRef args):
	AegisComponent("Light", ent), mLight_(nullptr)
{
	
	initLight();

	mDiffuse_ = Vector3(args["color_r"], args["color_g"], args["color_b"]);
	mSpecular_ = Vector3(args["spec_r"], args["spec_g"], args["spec_b"]);

	setLightColor(mDiffuse_);
	setSpecularColor(mSpecular_);

}

LightComponent::~LightComponent()
{
	delete mLight_;
}

LightComponent* CreateLight(Entity* ent, LuaRef ref ) {

	return new LightComponent(ent,ref);

}

inline Vector3 LightComponent::getLightColor() const
{
	 return mDiffuse_;
}

void LightComponent::setLightColor(Vector3 spec)
{
	mDiffuse_ = spec;
	mLight_->setLightColor(spec.x, spec.y, spec.z);
}

inline Vector3 LightComponent::getSpecularColor() const
{
	return mSpecular_;
}

void LightComponent::setSpecularColor(Vector3 spec)
{
	mSpecular_ = spec;
	mLight_->setSpecularColor(spec.x, spec.y, spec.z);
}

void LightComponent::setDirLight()
{
	mLight_->setDirLight();
}

void LightComponent::setPointLight()
{
	mLight_->setPointLight();
}

void LightComponent::setSpotLight()
{
	mLight_->setSpotLight();
}

void LightComponent::ConvertToLua(lua_State* state)
{
	getGlobalNamespace(state).
		beginNamespace("Aegis").
		beginNamespace("NativeComponents").
		addFunction("CreateLight", CreateLight).
		deriveClass<LightComponent, AegisComponent>("Light").
		addProperty("diffuse", &LightComponent::getLightColor, &LightComponent::setLightColor).
		addProperty("specular", &LightComponent::getSpecularColor, &LightComponent::setSpecularColor).
		endClass().
		endNamespace().
		endNamespace();

}

