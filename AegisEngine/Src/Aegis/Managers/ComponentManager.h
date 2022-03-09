
#include<functional>
#include <map>

#include "Singleton.h"
#include "Component.h"
#include <string>

class Entity;
typedef std::function<Component* (Entity*)> ComponentFactory;

class ComponentManager: public Singleton<ComponentManager>
{
    public:
        ComponentManager();
        ~ComponentManager();

        template<typename T>
        void registerComponent(const std::string& cmpID);

    private:
        void init();
        void close();

        ComponentFactory* getCmpFactory(const std::string factID);

        template <typename T>
        const std::string& getCmpID();
    
    
    std::map<std::string, ComponentFactory> mFactories_;
    std::map<std::string, std::string> mCmpIDs_;

};

template<typename T>
void ComponentManager::registerComponent(const std::string& cmpID)
{
    if (mFactories_.find(cmpID) == mFactories_.end())
    {
        mCmpIDs_[typeid(T).name()] = cmpID;
        //mFactories_[cmpID] = [](Entity* e) { return new T(e); };
        
    }
}

template<typename T>
inline const std::string& ComponentManager::getCmpID()
{
    return mCmpIDs_[typeid(T).name()];
}

