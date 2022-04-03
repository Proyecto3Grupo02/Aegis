#include "LightComponent.h"
#include "../Entity/Entity.h"

void LightComponent::initLight()
{
}

LightComponent::LightComponent(Entity* ent, Vector3 amb, Vector3 diff, Vector3 spec)
{
}

LightComponent::~LightComponent()
{
}

LightComponent* createLight(Entity* ent, LuaRef* ref ) {
	return new LightComponent(ent,NULL, NULL, NULL);
}

void LightComponent::ConvertToLua(lua_State* state)
{
}
