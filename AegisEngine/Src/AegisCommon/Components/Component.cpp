
#include "Component.h"
#include "../Entity/Entity.h"

Component::Component(): 
	mEntity_(nullptr), isActive_(true)
{
	
}

void Component::ConvertToLua(lua_State* state)
{
	getGlobalNamespace(state).
		beginNamespace("ECS").
		beginClass<Component>("ComponentBase").
		endClass().
		endNamespace();
}

