#include "AegisComponent.h"
#include "Entity.h"

AegisComponent* CreateComponent(std::string componentName, Entity* entity)
{
	return new AegisComponent(componentName, entity);
}

void AegisComponent::init()
{
	setCallbacks(funcs);
	callLuaRefFunc(initFunc, 0);
}

void AegisComponent::update(float dt)
{
	if (isActive_)
		callLuaRefFunc(updateFunc, dt);
}

void AegisComponent::lateUpdate(float dt)
{
	if (isActive_)
		callLuaRefFunc(lateUpdateFunc, dt);
}

void AegisComponent::fixedUpdate()
{
	if (isActive_)
		callLuaRefFunc(fixedUpdateFunc, 0);
}

void AegisComponent::onCollision(Entity* other)
{
	callLuaRefFunc(onCollisionEnterFunc, other);
}

void AegisComponent::onTrigger(Entity* other)
{
	callLuaRefFunc(onTriggerEnterFunc, other);
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

void AegisComponent::setData(LuaRef luaRef)
{
	//this function only exist to make data a parameter, but you can't overwrite data table
	printErrorModifyingTables("data", "table", true);
}

LuaRef AegisComponent::getData() const
{
	return data;
}

void AegisComponent::setType(LuaRef luaRef)
{
	type = luaRef;
}

void AegisComponent::setTypeLua(LuaRef luaRef)
{
	printErrorModifyingTables("type", "userdata", false);
}

LuaRef AegisComponent::getType() const
{
	return type;
}

void AegisComponent::setFuncs(LuaRef luaRef)
{
	//this function only exist to make data a parameter, but you can't overwrite funcs table
	printErrorModifyingTables("funcs", "table", true);
}

LuaRef AegisComponent::getFuncs() const
{
	return funcs;
}

void AegisComponent::ConvertToLua(lua_State* state)
{
	getGlobalNamespace(state).
		beginNamespace("Aegis").
		addFunction("CreateComponent", CreateComponent).
		deriveClass<AegisComponent, Component>("Component").
		addProperty("data", &AegisComponent::getData, &AegisComponent::setData).
		addProperty("funcs", &AegisComponent::getFuncs, &AegisComponent::setFuncs).
		addProperty("type", &AegisComponent::getType, &AegisComponent::setTypeLua).
		endClass().
		endNamespace();
}

void AegisComponent::printErrorModifyingTables(std::string fieldName, std::string typeName, bool modifiableFields)
{
#if defined _DEBUG
	std::string modifiable = modifiableFields ? "but you can modify its field\n" : "but you can read it\n";
	std::cout << "Error on " << getEntity()->getName() << " " << getComponentName() << "." << fieldName << ": ";
	std::cout << "You can't override this " << typeName << " with another one, " << modifiable;
#endif
}
