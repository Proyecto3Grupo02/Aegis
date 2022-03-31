#pragma once
#ifndef AEGIS_COMPONENT
#define AEGIS_COMPONENT
#include "Component.h"
#include "../Interfaces/ILuaObject.h"
#include <functional>

enum Callbacks {Update, LateUpdate, FixedUpdate, OnCollisionEnter, OnTriggerEnter};

#define LuaRefDefault LuaManager::getInstance()->GetEmptyLuaRef());

class Entity;
class	AegisComponent : public Component, public ILuaObject {
public: 
	AegisComponent() : Component() {}
	~AegisComponent(){}
	virtual void init() {}
	virtual void update(float dt) override;

	//Lua stuff
	static void ConvertToLua(lua_State* state);
	void setUpdate(LuaRef updateFunc);
	
	void SetData(LuaRef luaRef);
	LuaRef GetData() const;
private:
	LuaRef data = LuaManager::getInstance()->GetEmptyLuaRef();
	LuaRef updateFunc = LuaManager::getInstance()->GetEmptyLuaRef();
	LuaRef lateUpdateFunc = LuaManager::getInstance()->GetEmptyLuaRef();
	LuaRef fixedUpdateFunc = LuaManager::getInstance()->GetEmptyLuaRef();
	LuaRef onCollisionEnterFunc = LuaManager::getInstance()->GetEmptyLuaRef();
	LuaRef onTriggerEnterFunc = LuaManager::getInstance()->GetEmptyLuaRef();
};
#endif