#include "AegisComponent.h"

AegisComponent* CreateComponent(std::string componentName)
{
	AegisComponent* e = new AegisComponent();
	e->SetComponentName(componentName);
	return e;
}


void AegisComponent::init()
{
}

void AegisComponent::update(float dt)
{
	if (!updateFunc.isNil())
	{
		try {
			updateFunc(dt);
		}
		catch (LuaException const& e) {
			std::cout << e.what() << "\n";
		}
		
	}
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
