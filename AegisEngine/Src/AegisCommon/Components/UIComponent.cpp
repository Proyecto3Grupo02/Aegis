#include "UIComponent.h"

UIComponent::UIComponent(std::string componentName, UIElement* ent):
	Component(componentName,nullptr), mElement_(ent)
{
}

void UIComponent::init()
{
}

void UIComponent::render()
{
}

void UIComponent::OnMouse(UIElement* other)
{
	CallLuaRefFunc(OnMouseFunc, other);
}

void UIComponent::OnClickDown()
{
}

void UIComponent::OnClickUp()
{
}

void UIComponent::setCallbacks(LuaRef updateFunc)
{
}

void UIComponent::SetData(LuaRef luaRef)
{
}

LuaRef UIComponent::GetData() const
{
	return data;
}

void UIComponent::SetType(LuaRef luaRef)
{
	type = luaRef;
}

void UIComponent::SetTypeLua(LuaRef luaRef)
{
	PrintErrorModifyingTables("type", "userdata", false);
}

LuaRef UIComponent::GetType() const
{
	return type;
}

void UIComponent::SetFuncs(LuaRef luaRef)
{
	PrintErrorModifyingTables("funcs", "table", true);
}

LuaRef UIComponent::GetFuncs() const
{
	return funcs;
}
void UIComponent::ConvertToLua(lua_State* state)
{
	getGlobalNamespace(state).
		beginNamespace("Aegis").
		addFunction("CreateComponent", CreateComponent).
		deriveClass<UIComponent, Component>("Component").
				endClass().
		endNamespace();
}

void UIComponent::PrintErrorModifyingTables(std::string fieldName, std::string typeName, bool modifiableFields)
{
}

UIComponent* CreateComponent(std::string componentName, UIElement* elem)
{
	return new UIComponent(componentName, elem);
}