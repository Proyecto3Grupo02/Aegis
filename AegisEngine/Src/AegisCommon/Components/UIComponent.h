#pragma once
#ifndef UI_COMPONENT
#define UI_COMPONENT

#include "ILuaObject.h"
#include "Component.h"

enum UICallbacks { OnMouseOver, OnMouseExit, OnClickDown, OnClickReleased };

#define LuaRefDefault LuaManager::getInstance()->GetSharedEmptyLuaRef());


class UIElement;
class UIComponent:
	public Component, public ILuaObject
{
private:
	UIElement* mElement_;

	LuaRef type = LuaMngr()->getSharedEmptyLuaRef();
	LuaRef funcs = LuaMngr()->getNewEmptyTable();
	LuaRef initFunc = LuaMngr()->getSharedEmptyLuaRef();
	LuaRef onMouseFunc = LuaMngr()->getSharedEmptyLuaRef();
	LuaRef onMouseExitFunc = LuaMngr()->getSharedEmptyLuaRef();
	LuaRef onClickDownFunc = LuaMngr()->getSharedEmptyLuaRef();
	LuaRef onClickUpFunc = LuaMngr()->getSharedEmptyLuaRef();
protected:
	LuaRef data = LuaMngr()->getNewEmptyTable();

	template <class T>
	void SetDataAsInnerType(T* component);
public:
    UIComponent(std::string componentName);
    UIComponent(std::string componentName, UIElement* ent);
    virtual ~UIComponent() = default;

	virtual void init() override;
    virtual void render() override;
    virtual void onMouse(UIElement* other);

    virtual void onClickDown(UIElement* other);
    virtual void onClickUp(UIElement* other);

	inline UIElement* getElement() const { return mElement_; }

    //Lua stuff
	void setCallbacks(LuaRef updateFunc);

	void setData(LuaRef luaRef);
	LuaRef getData() const;

	void setType(LuaRef luaRef);
	void setTypeLua(LuaRef luaRef);
	LuaRef getType() const;

	void setFuncs(LuaRef luaRef);
	LuaRef getFuncs() const;

	static void ConvertToLua(lua_State* state);

	template <class T>
	void callLuaRefFunc(LuaRef func, T args = 0);
	// Soy consciente de que todos los cout deber�an llamarse desde otro lado, pero por ahora aqui
	void printErrorModifyingTables(std::string fieldName, std::string typeName, bool modifiableFields);
};

#endif
