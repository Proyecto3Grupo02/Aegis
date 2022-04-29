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

void UIComponent::OnClickDown(UIElement* other)
{
	CallLuaRefFunc(OnClickDownFunc, other);
}

void UIComponent::OnClickUp(UIElement* other)
{
	CallLuaRefFunc(OnClickUpFunc, other);
}

void UIComponent::setCallbacks(LuaRef updateFunc)
{
	this->initFunc = funcs["init"];
	this->OnClickDownFunc = funcs["OnClickDown"];
	this->OnClickUpFunc = funcs["OnClickUp"];
	this->OnMouseFunc = funcs["OnMouse"];
	this->OnMouseExitFunc = funcs["OnMouseExit"];
}

void UIComponent::SetData(LuaRef luaRef)
{
	PrintErrorModifyingTables("data", "table", true);
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
#if defined _DEBUG
	std::string modifiable = modifiableFields ? "but you can modify its field\n" : "but you can read it\n";
	std::cout << "Error on " << getEntity()->getName() << " " << GetComponentName() << "." << fieldName << ": ";
	std::cout << "You can't override this " << typeName << " with another one, " << modifiable;
#endif
}

UIComponent* CreateComponent(std::string componentName, UIElement* elem)
{
	return new UIComponent(componentName, elem);
}