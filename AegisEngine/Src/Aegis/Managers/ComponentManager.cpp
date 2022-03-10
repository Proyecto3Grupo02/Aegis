
#include "ComponentManager.h"


ComponentManager::ComponentManager()
{
}

ComponentManager::~ComponentManager()
{
}

void ComponentManager::init()
{
}

void ComponentManager::close()
{
	mFactories_.clear();
	deleteInstance();
}

ComponentFactory* ComponentManager::getCmpFactory(const std::string factID)
{
	if (mFactories_.find(factID) != mFactories_.end()) {
		return &mFactories_[factID];
	}
	return nullptr;
}

