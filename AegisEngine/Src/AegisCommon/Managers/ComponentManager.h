#pragma once
#ifndef  COMPONENT_MANAGER 
#define COMPONENT_MANAGER

#include "../Utils/Singleton.h" //Da error en el cpp
#include "../../checkML.h" //BASURA
#include <map>
#include <functional>
#include <unordered_map>

class Component;
class Entity;

typedef std::function<Component* (Entity*)> ComponentFactory;
class ComponentManager: public Singleton<ComponentManager> {
public:
	ComponentManager();
	virtual ~ComponentManager();
	
	template<typename T>
	void RegisterComponent(std::string id);

	template <typename T>
	const std::string GetID();

	void close();

private:
	std::unordered_map<std::string, std::string> mComponentTypes_;
	std::map <std::string, ComponentFactory> mComponentFactory_;
};

#endif // ! COMPONENT_MANAGER 

template<typename T>
void ComponentManager::RegisterComponent(std::string id) {
	std::string typeName = typeid(T).name();

	if (mComponentTypes_.find(typeName) == mComponentTypes_.end()) {
		mComponentTypes_[typeName] = id;
	}
}

template<typename T>
const std::string ComponentManager::GetID() {
	std::string typeName = typeid(T).name();
	return mComponentTypes_[typeName];
}