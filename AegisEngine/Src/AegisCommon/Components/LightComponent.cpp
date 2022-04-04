#include "LightComponent.h"
#include "../Entity/Entity.h"

void LightComponent::initLight()
{
	mLight_ = new AegisLight(getEntity()->getNode()->getCreator());
}

LightComponent::LightComponent(Entity* ent,LuaRef args):
	AegisComponent("Light", ent), mLight_(nullptr)
{
	
	initLight();

	mDiffuse_ = Vector3(args["color_r"], args["color_g"], args["color_b"]);
	mSpecular_ = Vector3(args["spec_r"], args["spec_g"], args["spec_b"]);

	setLightColor(mDiffuse_.x, mDiffuse_.y, mDiffuse_.z);
	setSpecularColor(mSpecular_.x, mSpecular_.y, mSpecular_.z);

}

LightComponent::~LightComponent()
{
	delete mLight_;
}

LightComponent* createLight(Entity* ent, LuaRef ref ) {

	return new LightComponent(ent,ref);

}

void LightComponent::setLightColor(float r, float g, float b)
{
	mDiffuse_ = Vector3(r, g, b);
	mLight_->setLightColor(r, g, b);

}

void LightComponent::setSpecularColor(float r, float g, float b)
{
	mSpecular_ = Vector3(r, g, b);
	mLight_->setSpecularColor(r, g, b);
}

void LightComponent::ConvertToLua(lua_State* state)
{
	getGlobalNamespace(state).
		beginNamespace("Aegis").
		beginNamespace("NativeComponents").
		addFunction("createLight", createLight).
		deriveClass<LightComponent, AegisComponent>("Light").
		addProperty("diffuse", &LightComponent::getLightColor, &LightComponent::setLightColor).
		addProperty("specular", &LightComponent::getSpecularColor, &LightComponent::setSpecularColor).
		endClass().
		endNamespace().
		endNamespace();

}

