﻿#pragma once
#ifndef UI_COMPONENT
#define UI_COMPONENT

#include "../Interfaces/ILuaObject.h"
#include "Component.h"

enum UICallbacks { OnMouseOver, OnMouseExit, OnClickDown, OnClickReleased };

#define LuaRefDefault LuaManager::getInstance()->GetSharedEmptyLuaRef());


class UIElement;
class UIComponent:
	public Component, public ILuaObject
{
private:
	UIElement* mElement_;

	LuaRef type = LuaMngr()->GetSharedEmptyLuaRef();
	LuaRef funcs = LuaMngr()->GetNewEmptyTable();
	LuaRef initFunc = LuaMngr()->GetSharedEmptyLuaRef();
	LuaRef OnMouseFunc = LuaMngr()->GetSharedEmptyLuaRef();
	LuaRef OnMouseExitFunc = LuaMngr()->GetSharedEmptyLuaRef();
	LuaRef OnClickDownFunc = LuaMngr()->GetSharedEmptyLuaRef();
	LuaRef OnClickUpFunc = LuaMngr()->GetSharedEmptyLuaRef();
protected:
	LuaRef data = LuaMngr()->GetNewEmptyTable();

	template <class T>
	void SetDataAsInnerType(T* component);
public:
    UIComponent(std::string componentName);
    //UIComponent(std::string componentName, UIElement* ent);
    virtual ~UIComponent() = default;

	virtual void init() override;
    virtual void render() override;
 //   virtual void OnMouse(UIElement* other);

 //   virtual void OnClickDown(UIElement* other);
 //   virtual void OnClickUp(UIElement* other);

	inline UIElement* getElement() const { return mElement_; }

    //Lua stuff
	void setCallbacks(LuaRef updateFunc);

	void SetData(LuaRef luaRef);
	LuaRef GetData() const;

	void SetType(LuaRef luaRef);
	void SetTypeLua(LuaRef luaRef);
	LuaRef GetType() const;

	void SetFuncs(LuaRef luaRef);
	LuaRef GetFuncs() const;

	static void ConvertToLua(lua_State* state);

	template <class T>
	void CallLuaRefFunc(LuaRef func, T args = 0);
	// Soy consciente de que todos los cout deber�an llamarse desde otro lado, pero por ahora aqui
	void PrintErrorModifyingTables(std::string fieldName, std::string typeName, bool modifiableFields);
};

#endif
