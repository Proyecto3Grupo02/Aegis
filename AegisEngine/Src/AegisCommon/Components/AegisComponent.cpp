#include "AegisComponent.h"

AegisComponent* CreateComponent(std::string componentName)
{
	AegisComponent* e = new AegisComponent();
	e->SetComponentName(componentName);
	return e;
}


void AegisComponent::init()
{
	CallLuaRefFunc(initFunc, 0);
}

void AegisComponent::update(float dt)
{
	CallLuaRefFunc(updateFunc, dt);
}

void AegisComponent::lateUpdate(float dt)
{
	CallLuaRefFunc(lateUpdateFunc, dt);
}

void AegisComponent::fixedUpdate()
{
	CallLuaRefFunc(fixedUpdateFunc, 0);
}

void AegisComponent::onCollision(Entity* other)
{
	CallLuaRefFunc(onCollisionEnterFunc, other);
}

void AegisComponent::onTrigger(Entity* other)
{
	CallLuaRefFunc(onTriggerEnterFunc, other);
}


void AegisComponent::setCallbacks(LuaRef updateFunc)
{
	this->initFunc = updateFunc.rawget("init");
	this->updateFunc = updateFunc.rawget("update");
	this->lateUpdateFunc = updateFunc.rawget("lateUpdate");
	this->fixedUpdateFunc = updateFunc.rawget("fixedUpdate");
	this->onCollisionEnterFunc = updateFunc.rawget("onCollisionEnter");
	this->onTriggerEnterFunc = updateFunc.rawget("onTriggerEnter");
}

LuaRef AegisComponent::GetData() const
{
	return data;
}

void AegisComponent::SetExternalData(LuaRef luaRef)
{
	external = luaRef;
}

LuaRef AegisComponent::GetExtenalData() const
{
	return external;
}

void AegisComponent::SetType(LuaRef luaRef)
{
	type = luaRef;
}

LuaRef AegisComponent::GetType() const
{
	return type;
}


void AegisComponent::SetData(LuaRef luaRef)
{
	data = luaRef;
}

void AegisComponent::ConvertToLua(lua_State* state)
{
	getGlobalNamespace(state).
		beginNamespace("Aegis").
		addFunction("CreateComponent", CreateComponent).
		deriveClass<AegisComponent, Component>("Component").
		addFunction("SetCallbacks", &AegisComponent::setCallbacks).
		addProperty("data", &AegisComponent::GetData, &AegisComponent::SetData).
		addProperty("external", &AegisComponent::GetExtenalData, &AegisComponent::SetExternalData).
		addProperty("type", &AegisComponent::GetType, &AegisComponent::SetType).
		endClass().
		endNamespace();
}
