#pragma once
#ifndef UI_COMPONENT
#define UI_COMPONENT

#include "../Interfaces/ILuaObject.h"
#include "Component.h"

enum UICallbacks { OnMouseOver, OnMouseExit, OnClickDown, OnClickReleased };

#define LuaRefDefault LuaManager::getInstance()->GetSharedEmptyLuaRef());


struct UIElement;
class UIComponent: public Component, public ILuaObject
{
private:
    /* data */
public:
    UIComponent(std::string componentName, UIElement* ent);
    virtual ~UIComponent() = default;

    virtual void render() = 0;
    virtual void OnMouse()=0;

    virtual void OnClickDown()=0;
    virtual void OnClickUp()=0;


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