#pragma once
#ifndef AEGIS_COMPONENT
#define AEGIS_COMPONENT
#include "Component.h"
#include "../Interfaces/ILuaObject.h"
#include <functional>

enum Callbacks { Update, LateUpdate, FixedUpdate, OnCollisionEnter, OnTriggerEnter };

#define LuaRefDefault LuaManager::getInstance()->GetSharedEmptyLuaRef());

struct Entity;
class	AegisComponent : public Component, public ILuaObject {
public:
	AegisComponent() : Component() {}
	AegisComponent(std::string componentName, Entity* entity) : Component(componentName, entity) {}
	~AegisComponent() {}
	virtual void init() override;
	virtual void update(float dt) override;
	virtual void lateUpdate(float dt)  override;
	virtual void fixedUpdate()  override;
	virtual void onCollision(Entity* other)  override;
	virtual void onTrigger(Entity* other) override;

	//Lua stuff
	void setCallbacks(LuaRef updateFunc);

	void SetData(LuaRef luaRef);
	LuaRef GetData() const;

	void SetExternalData(LuaRef luaRef);
	LuaRef GetExtenalData() const;

	void SetType(LuaRef luaRef);
	void SetTypeLua(LuaRef luaRef);
	LuaRef GetType() const;

	void SetFuncs(LuaRef luaRef);
	LuaRef GetFuncs() const;

	static void ConvertToLua(lua_State* state);

	template <class T>
	void CallLuaRefFunc(LuaRef func, T args = 0);
	// Soy consciente de que todos los cout deberían llamarse desde otro lado, pero por ahora aqui
	void PrintErrorModifyingTables(std::string fieldName, std::string typeName, bool modifiableFields);
protected:
	LuaRef data =LuaMngr()->GetNewEmptyTable();
private:
	LuaRef external =LuaMngr()->GetNewEmptyTable();
	LuaRef type =LuaMngr()->GetSharedEmptyLuaRef();
	LuaRef funcs =LuaMngr()->GetNewEmptyTable();
	LuaRef initFunc =LuaMngr()->GetSharedEmptyLuaRef();
	LuaRef updateFunc =LuaMngr()->GetSharedEmptyLuaRef();
	LuaRef lateUpdateFunc =LuaMngr()->GetSharedEmptyLuaRef();
	LuaRef fixedUpdateFunc =LuaMngr()->GetSharedEmptyLuaRef();
	LuaRef onCollisionEnterFunc =LuaMngr()->GetSharedEmptyLuaRef();
	LuaRef onTriggerEnterFunc =LuaMngr()->GetSharedEmptyLuaRef();

protected:
	template <class T>
	void SetDataAsInnerType(T* component);
};
#endif

template<class T>
inline void AegisComponent::CallLuaRefFunc(LuaRef func, T args)
{
#if defined _DEBUG
	if (!func.isNil())
	{
		try {
			func(args);
		}
		catch (LuaException const& e) {
			std::cout << e.what() << "\n";
		}

	}
#else
	if (!func.isNil())
		func(args);
#endif
}

template<class T>
inline void AegisComponent::SetDataAsInnerType(T* component)
{
	SetType(LuaRef(LuaManager::getInstance()->GetState(), component));
}
