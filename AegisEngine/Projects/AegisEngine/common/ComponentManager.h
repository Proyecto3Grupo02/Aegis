
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
