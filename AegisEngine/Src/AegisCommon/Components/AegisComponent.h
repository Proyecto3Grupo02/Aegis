#pragma once
#ifndef AEGIS_COMPONENT
#define AEGIS_COMPONENT
#include "Component.h"
#include "../Interfaces/ILuaObject.h"
#include <functional>

enum Callbacks {Update, LateUpdate, FixedUpdate, OnCollisionEnter, OnTriggerEnter};

#define LuaRefDefault LuaManager::getInstance()->GetEmptyLuaRef());

struct Entity;
class	AegisComponent : public Component, public ILuaObject {
public: 
	AegisComponent() : Component() {}
	~AegisComponent(){}
	virtual void init() {}
	virtual void update(float dt) override;
	virtual void lateUpdate(float dt)  override;
	virtual void fixedUpdate()  override;
	virtual void onCollision(Entity* other)  override;
	virtual void onTrigger(Entity* other) override;

	//Lua stuff
	void setCallbacks(LuaRef updateFunc);
	
	void SetData(LuaRef luaRef);
	LuaRef GetData() const;
	
	static void ConvertToLua(lua_State* state);
private:
	LuaRef data = LuaManager::getInstance()->GetEmptyLuaRef();
	LuaRef updateFunc = LuaManager::getInstance()->GetEmptyLuaRef();
	LuaRef lateUpdateFunc = LuaManager::getInstance()->GetEmptyLuaRef();
	LuaRef fixedUpdateFunc = LuaManager::getInstance()->GetEmptyLuaRef();
	LuaRef onCollisionEnterFunc = LuaManager::getInstance()->GetEmptyLuaRef();
	LuaRef onTriggerEnterFunc = LuaManager::getInstance()->GetEmptyLuaRef();
};
#endif