#pragma once
#ifndef AEGIS_COMPONENT
#define AEGIS_COMPONENT
#include "Component.h"
#include "../Interfaces/ILuaObject.h"
#include <functional>

enum Callbacks { Update, LateUpdate, FixedUpdate, OnCollisionEnter, OnTriggerEnter };

#define LuaRefDefault LuaManager::getInstance()->GetEmptyLuaRef());

struct Entity;
class	AegisComponent : public Component, public ILuaObject {
public:
	AegisComponent() : Component() {}
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
	LuaRef GetType() const;

	static void ConvertToLua(lua_State* state);

	template <class T>
	void CallLuaRefFunc(LuaRef func, T args = 0);
private:
	LuaRef data = LuaManager::getInstance()->GetEmptyLuaRef();
	LuaRef external = LuaManager::getInstance()->GetEmptyLuaRef();
	LuaRef type = LuaManager::getInstance()->GetEmptyLuaRef();
	LuaRef initFunc = LuaManager::getInstance()->GetEmptyLuaRef();
	LuaRef updateFunc = LuaManager::getInstance()->GetEmptyLuaRef();
	LuaRef lateUpdateFunc = LuaManager::getInstance()->GetEmptyLuaRef();
	LuaRef fixedUpdateFunc = LuaManager::getInstance()->GetEmptyLuaRef();
	LuaRef onCollisionEnterFunc = LuaManager::getInstance()->GetEmptyLuaRef();
	LuaRef onTriggerEnterFunc = LuaManager::getInstance()->GetEmptyLuaRef();

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
