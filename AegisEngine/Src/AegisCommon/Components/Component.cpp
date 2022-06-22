#include "Component.h"

Component::Component(): 
	mEntity_(nullptr), isActive_(true) {
	
}

Component::Component(std::string componentName, Entity* entity) 
	:	componentName(componentName), mEntity_(entity), isActive_(true) {
}

void Component::ConvertToLua(lua_State* state)
{
	getGlobalNamespace(state).
		beginNamespace("Aegis").
		beginClass<Component>("ComponentBase").
		addProperty("name", &Component::getComponentName).
		addProperty("entity", &Component::getEntity).
		addProperty("enabled", &Component::getActive, &Component::setActive).
		endClass().
		endNamespace();
}

