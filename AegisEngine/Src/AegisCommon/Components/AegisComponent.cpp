#include "AegisComponent.h"

AegisComponent* CreateComponent()
{
	AegisComponent* e = new AegisComponent();
	return e;
}

void TestAegisComponent(AegisComponent component)
{
	component.doUpdate(0.16f);
}

void AegisComponent::ConvertToLua(lua_State* state)
{
	getGlobalNamespace(state).
		beginNamespace("ECS").
		addFunction("CreateComponent", CreateComponent).
		addFunction("TestAegisComponent", TestAegisComponent).
		deriveClass<AegisComponent, Component>("Component").
		addProperty("update", &AegisComponent::getUpdate, &AegisComponent::setUpdate).
		addProperty("data", &AegisComponent::GetData, &AegisComponent::SetData).
		endClass().
		endNamespace();
}

void AegisComponent::setUpdate(LuaRef updateFunc)
{
	this->doUpdate = [updateFunc](float n) { updateFunc(n); };
}

std::function<void(float)> AegisComponent::getUpdate() const
{
	return doUpdate;
}

void AegisComponent::SetData(LuaRef luaRef)
{
	if(data.empty())
		data.push_back(luaRef);
}

LuaRef AegisComponent::GetData() const
{
	return data[0];
}
