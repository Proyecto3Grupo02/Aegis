#pragma once
#include "ComponentManager.h"
class Component;
class Entity;
class ComponentManager;
class Scene;
//
//class ComponentFactory {
//public:
//	ComponentFactory() = default;
//	virtual ~ComponentFactory() = default;
//	virtual Component* create(Entity* entity) = 0;
//};

//macro for selfdeclaration of the components
#define DECLARE(cmpName) \
class CmpName##Factory final: public ComponentFactory{  \
public:													\
	CmpName##Factory();									\
	Component* create(Entity* entity) override;			\
};														\
\
class CmpName##FactoryRegister{							\
public:													\
	CmpName##FactoryRegister();							\
};														\

#define DEFINE(CmpName)									\
														\
CmpName##FactoryRegister::CmpName##FactoryRegister() {	\
	ComponentManager::getInstance()->											\
}														\
