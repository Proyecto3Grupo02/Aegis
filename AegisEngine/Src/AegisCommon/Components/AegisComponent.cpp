#include "AegisComponent.h"

AegisComponent* CreateComponent()
{
	AegisComponent* e = new AegisComponent();
	return e;
}


void AegisComponent::update(float dt)
{
	if (!updateFunc.isNil())
		updateFunc(dt);

	//if (doUpdate != nullptr) 
	//	doUpdate(dt);
}

void AegisComponent::ConvertToLua(lua_State* state)
{
	getGlobalNamespace(state).
		beginNamespace("ECS").
		addFunction("CreateComponent", CreateComponent).
		deriveClass<AegisComponent, Component>("Component").
		addFunction("setUpdate", &AegisComponent::setUpdate).
		addProperty("data", &AegisComponent::GetData, &AegisComponent::SetData).
		endClass().
		endNamespace();
}

void AegisComponent::setUpdate(LuaRef updateFunc)
{
	this->updateFunc = updateFunc;
}

void AegisComponent::SetData(LuaRef luaRef)
{
	float time = luaRef.rawget("time");
	data = luaRef;
}

LuaRef AegisComponent::GetData() const
{
	return data;
}
