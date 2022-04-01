
#include "Component.h"
#include "../Entity/Entity.h"

Component::Component(): 
	mEntity_(nullptr), isActive_(true)
{
	
}

void Component::ConvertToLua(lua_State* state)
{
	getGlobalNamespace(state).
		beginNamespace("Aegis").
		beginClass<Component>("ComponentBase").
		addProperty("name", &Component::GetComponentName, &Component::SetComponentName).
		addProperty("entity", &Component::GetEntity, &Component::SetEntity).
		endClass().
		endNamespace();
}

