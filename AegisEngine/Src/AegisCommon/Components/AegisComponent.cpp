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
}

void AegisComponent::lateUpdate(float dt)
{
	if (!lateUpdateFunc.isNil())
		lateUpdateFunc(dt);
}

void AegisComponent::fixedUpdate()
{
	if (!fixedUpdateFunc.isNil())
		fixedUpdateFunc();
}

void AegisComponent::onCollision(Entity* other)
{
	if (!onCollisionEnterFunc.isNil())
		onCollisionEnterFunc(other);
}

void AegisComponent::onTrigger(Entity* other)
{
	if (!onTriggerEnterFunc.isNil())
		onTriggerEnterFunc(other);
}


void AegisComponent::setCallbacks(LuaRef updateFunc)
{
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


void AegisComponent::SetData(LuaRef luaRef)
{
	data = luaRef;
}

void AegisComponent::ConvertToLua(lua_State* state)
{
	getGlobalNamespace(state).
		beginNamespace("ECS").
		addFunction("CreateComponent", CreateComponent).
		deriveClass<AegisComponent, Component>("Component").
		addFunction("setCallbacks", &AegisComponent::setCallbacks).
		addProperty("data", &AegisComponent::GetData, &AegisComponent::SetData).
		endClass().
		endNamespace();
}