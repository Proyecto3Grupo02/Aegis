#pragma once
#ifndef AEGIS_COMPONENT
#define AEGIS_COMPONENT

#include "Component.h"
#include "ILuaObject.h"
#include <functional>

enum Callbacks { Update, LateUpdate, FixedUpdate, OnCollisionEnter, OnTriggerEnter };

#define LuaRefDefault LuaManager::getInstance()->GetSharedEmptyLuaRef());

struct Entity;
class	AegisComponent : public Component, public ILuaObject {
public:
	AegisComponent() : Component() {}
	AegisComponent(std::string componentName, Entity* entity) : Component(componentName, entity) {}
	virtual ~AegisComponent() {}
	virtual void init() override;
	virtual void update(float dt) override;
	virtual void lateUpdate(float dt)  override;
	virtual void fixedUpdate()  override;
	virtual void onCollision(Entity* other)  override;
	virtual void onTrigger(Entity* other) override;

	//SETS-------------------------------------
	void setCallbacks(LuaRef updateFunc);
	void setData(LuaRef luaRef);
	void setType(LuaRef luaRef);
	void setTypeLua(LuaRef luaRef);
	void setFuncs(LuaRef luaRef);

	//GETS--------------------------------------
	LuaRef getData() const;
	LuaRef getType() const;
	LuaRef getFuncs() const;

	static void ConvertToLua(lua_State* state);

	template <class T>
	void callLuaRefFunc(LuaRef func, T args = 0);
	// Soy consciente de que todos los cout deber�an llamarse desde otro lado, pero por ahora aqui
	void printErrorModifyingTables(std::string fieldName, std::string typeName, bool modifiableFields);

protected:
	LuaRef data =LuaMngr()->getNewEmptyTable();
	template <class T>
	void setDataAsInnerType(T* component);

private:
	LuaRef type =LuaMngr()->getSharedEmptyLuaRef();
	LuaRef funcs =LuaMngr()->getNewEmptyTable();
	LuaRef initFunc =LuaMngr()->getSharedEmptyLuaRef();
	LuaRef updateFunc =LuaMngr()->getSharedEmptyLuaRef();
	LuaRef lateUpdateFunc =LuaMngr()->getSharedEmptyLuaRef();
	LuaRef fixedUpdateFunc =LuaMngr()->getSharedEmptyLuaRef();
	LuaRef onCollisionEnterFunc =LuaMngr()->getSharedEmptyLuaRef();
	LuaRef onTriggerEnterFunc =LuaMngr()->getSharedEmptyLuaRef();
};
#endif

template<class T>
inline void AegisComponent::callLuaRefFunc(LuaRef func, T args)
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
inline void AegisComponent::setDataAsInnerType(T* component)
{
	setType(LuaRef(LuaManager::getInstance()->getState(), component));
}
