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
	return nullptr;
}

template<typename T>
void ComponentManager::registerComponent(const std::string& cmpID)
{
	if (mFactories_.find(nameID) != mFactories_.end())
	{
		return;
	}
	mCmpIDs_[typeid(T).name()] = nameID;
	mFactories_[nameID] = [](Entity* entity) { return new T(Entity); };
}

template<typename T>
inline const std::string& ComponentManager::getCmpID()
{
	return mCmpsIDs_[typeid(T).name()];
}