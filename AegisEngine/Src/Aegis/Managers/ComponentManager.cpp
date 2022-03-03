//#include "ComponentManager.h"
//
//ComponentManager::ComponentManager()
//{
//}
//
//ComponentManager::~ComponentManager()
//{
//}
//
//void ComponentManager::init()
//{
//}
//
//void ComponentManager::close()
//{
//	mFactories_.clear();
//	deleteInstance();
//}
//
//ComponentFactory* ComponentManager::getCmpFactory(const std::string factID)
//{
//	if (mFactories_.find(factID) != mFactories_.end()) {
//		return &mFactories_[factID];
//	}
//	return nullptr;
//}
//
//template<typename T>
//void ComponentManager::registerComponent(const std::string& cmpID)
//{
//	if (mFactories_.find(cmpID) != mFactories_.end())
//	{
//		return;
//	}
//	mCmpIDs_[typeid(T).name()] = cmpID;
//	mFactories_[cmpID] = [](Entity* entity) { return new T(Entity); };
//}
//
//template<typename T>
//inline const std::string& ComponentManager::getCmpID()
//{
//	return mCmpIDs_[typeid(T).name()];
//}