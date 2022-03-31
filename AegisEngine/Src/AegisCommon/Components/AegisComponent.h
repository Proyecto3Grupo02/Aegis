#pragma once
#ifndef AEGIS_COMPONENT
#define AEGIS_COMPONENT
#include "Component.h"
#include "../Interfaces/ILuaObject.h"
#include <functional>

class Entity;
class	AegisComponent : public Component, public ILuaObject {
public: 
	AegisComponent() : Component(){}
	~AegisComponent(){}
	virtual void init() {}

	static void ConvertToLua(lua_State* state);
	std::function<void(float)> doUpdate;
	void setUpdate(LuaRef updateFunc);
	std::function<void(float)> getUpdate() const;
	
	void SetData(LuaRef luaRef);
	LuaRef GetData() const;
private:
	std::vector<LuaRef> data;
};
#endif