#pragma once
#ifndef  COMPONENT_H 
#define COMPONENT_H

#include <Ogre.h>
#include "ILuaObject.h"
#include <string>

struct Entity;

class Component : public ILuaObject {
    public:
       Component();
       Component(std::string componentName, Entity* entity);

       virtual ~Component()=default;

       inline Entity* getEntity() { return mEntity_; }
       Entity* getEntity() const 
       { 
           return mEntity_; 
       };
       //void SetEntity(Entity* entity) { mEntity_ = entity; }

       virtual void init()=0;       
       virtual void fixedUpdate() {};
       virtual void update(float dt) {};
       virtual void lateUpdate(float dt) {};
       virtual void render() {};

       virtual void onCollision(Entity* other) {};
       virtual void onTrigger(Entity* other) {};

       bool getActive() { return isActive_; }
       void setActive(bool active) { isActive_ = active; }

       std::string getComponentName() const { return componentName; };
       void setComponentNameLua(std::string name) 
       { 
           std::cout << "You can't override component name, but you can read it.";
           std::cout << "Component name can only be ser through Aegis.CreateComponent\n";
       };
       void setComponentName(std::string name)
       {
           this->componentName = name;
       };

       void setEntityLua(Entity* entity)
       { 
           std::cout << "You can't override component entity, but you can read it.";
           std::cout << "Component entity can only be ser through Aegis.CreateComponent\n";
       };
       
       static void ConvertToLua(lua_State* state);
    protected:
        Entity* mEntity_;
        bool isActive_;
        std::string componentName;  
};

#endif // ! COMPONENT_H


