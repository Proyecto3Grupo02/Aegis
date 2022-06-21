#include "UIComponent.h"

UIComponent::UIComponent(std::string componentName, UIElement* ent):
	Component(componentName,nullptr), mElement_(ent)
{
}

UIComponent::UIComponent(std::string componentName) :
	Component(componentName, nullptr)
{
}

void UIComponent::init()
{
}

void UIComponent::render()
{
}

void UIComponent::onMouse(UIElement* other)
{
	callLuaRefFunc(onMouseFunc, other);
}

void UIComponent::onClickDown(UIElement* other)
{
	callLuaRefFunc(onClickDownFunc, other);
}

void UIComponent::onClickUp(UIElement* other)
{
	callLuaRefFunc(onClickUpFunc, other);
}

void UIComponent::setCallbacks(LuaRef updateFunc)
{
	this->initFunc = funcs["init"];
	this->onClickDownFunc = funcs["OnClickDown"];
	this->onClickUpFunc = funcs["OnClickUp"];
	this->onMouseFunc = funcs["OnMouse"];
	this->onMouseExitFunc = funcs["OnMouseExit"];
}

void UIComponent::setData(LuaRef luaRef)
{
	printErrorModifyingTables("data", "table", true);
}

LuaRef UIComponent::getData() const
{
	return data;
}

void UIComponent::setType(LuaRef luaRef)
{
	type = luaRef;
}

void UIComponent::setTypeLua(LuaRef luaRef)
{
	printErrorModifyingTables("type", "userdata", false);
}

LuaRef UIComponent::getType() const
{
	return type;
}

void UIComponent::setFuncs(LuaRef luaRef)
{
	printErrorModifyingTables("funcs", "table", true);
}

LuaRef UIComponent::getFuncs() const
{
	return funcs;
}
void UIComponent::ConvertToLua(lua_State* state)
{

}

void UIComponent::printErrorModifyingTables(std::string fieldName, std::string typeName, bool modifiableFields)
{
//#if defined _DEBUG
//	std::string modifiable = modifiableFields ? "but you can modify its field\n" : "but you can read it\n";
//	std::cout << "Error on " <<mElement_->getName() << " " << GetComponentName() << "." << fieldName << ": ";
//	std::cout << "You can't override this " << typeName << " with another one, " << modifiable;
//#endif
}

UIComponent* CreateComponent(std::string componentName, UIElement* elem)
{
	return new UIComponent(componentName, elem);
}

template<class T>
void UIComponent::callLuaRefFunc(LuaRef func, T args)
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
void UIComponent::SetDataAsInnerType(T* component)
{
	SetType(LuaRef(LuaManager::getInstance()->GetState(), component));
}
