#include "AegisComponent.h"
#include "../Entity/Entity.h"

AegisComponent* CreateComponent(std::string componentName, Entity* entity)
{
	return new AegisComponent(componentName, entity);
}


void AegisComponent::init()
{
	// Not all components will have dependencies, it's better to free the able and set this to nil
	if (!external.isNil() && external["inited"].isNil()) 
		external = Nil();

	setCallbacks(funcs);
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


void AegisComponent::setCallbacks(LuaRef funcs)
{
	this->initFunc = funcs["init"];
	this->updateFunc = funcs["update"];
	this->lateUpdateFunc = funcs["lateUpdate"];
	this->fixedUpdateFunc = funcs["fixedUpdate"];
	this->onCollisionEnterFunc = funcs["onCollisionEnter"];
	this->onTriggerEnterFunc = funcs["onTriggerEnter"];
}

void AegisComponent::SetData(LuaRef luaRef)
{
	//this function only exist to make data a parameter, but you can't overwrite data table
	PrintErrorModifyingTables("data", "table", true);
}

LuaRef AegisComponent::GetData() const
{
	return data;
}

void AegisComponent::SetExternalData(LuaRef luaRef)
{
	PrintErrorModifyingTables("external", "table", true);
}

LuaRef AegisComponent::GetExtenalData() const
{
	return external;
}

void AegisComponent::SetType(LuaRef luaRef)
{
	type = luaRef;
}

void AegisComponent::SetTypeLua(LuaRef luaRef)
{
	PrintErrorModifyingTables("type", "userdata", false);
}

LuaRef AegisComponent::GetType() const
{
	return type;
}

void AegisComponent::SetFuncs(LuaRef luaRef)
{
	//this function only exist to make data a parameter, but you can't overwrite funcs table
	PrintErrorModifyingTables("funcs", "table", true);
}

LuaRef AegisComponent::GetFuncs() const
{
	return funcs;
}

void AegisComponent::ConvertToLua(lua_State* state)
{
	getGlobalNamespace(state).
		beginNamespace("Aegis").
		addFunction("CreateComponent", CreateComponent).
		deriveClass<AegisComponent, Component>("Component").
		addProperty("data", &AegisComponent::GetData, &AegisComponent::SetData).
		addProperty("funcs", &AegisComponent::GetFuncs, &AegisComponent::SetFuncs).
		addProperty("external", &AegisComponent::GetExtenalData, &AegisComponent::SetExternalData).
		addProperty("type", &AegisComponent::GetType, &AegisComponent::SetTypeLua).
		endClass().
		endNamespace();
}

void AegisComponent::PrintErrorModifyingTables(std::string fieldName, std::string typeName, bool modifiableFields)
{
#if defined _DEBUG
	std::string modifiable = modifiableFields ? "but you can modify its field\n" : "but you can read it\n";
	std::cout << "Error on " << getEntity()->getName() << " " << GetComponentName() << "." << fieldName << ": ";
	std::cout << "You can't override this " << typeName << " with another one, " << modifiable;
#endif
}
