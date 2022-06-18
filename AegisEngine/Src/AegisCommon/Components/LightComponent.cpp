#include "LightComponent.h"
#include "Entity.h"

LightComponent::LightComponent(Entity* ent, LuaRef args) :
	AegisComponent("Light", ent), mLight_(new AegisLight(ent->getNode(), ent->getNode()->getCreator()))
{
	data = args;

	setLightType(LuaMngr()->ParseString(args["lightType"], "PointLight"));
	if (!args["direction"].isNil())
		setDirection(Vector3::ParseVector3(args["direction"]));
	mDiffuse_ = Vector3::ParseVector3(args["color"], Vector3Mode::RGB);
	mSpecular_ = Vector3::ParseVector3(args["spec"], Vector3Mode::RGB);

	setLightColor(mDiffuse_);
	setSpecularColor(mSpecular_);
	
	SetDataAsInnerType(this);	
}

LightComponent::~LightComponent()
{
	delete mLight_;
}

LightComponent* CreateLight(Entity* ent, LuaRef ref) {

	return new LightComponent(ent, ref);

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

void LightComponent::setLightType(std::string lightType)
{
	mLight_->setLightType(lightType);
}

void LightComponent::setDirection(Vector3 dir)
{
	// Si el transform está activo actualizará la rotación y eso a su vez invalida la dirección
	mEntity_->GetTransform()->setActive(false);
	mLight_->setDirection(dir.x, dir.y, dir.z);
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
		addFunction("SetDirection", &LightComponent::setDirection).
		endClass().
		endNamespace().
		endNamespace();

}

