#pragma once
#ifndef  COMPONENT_H 
#define COMPONENT_H

#include <Ogre.h>
#include <string>
#include "ILuaObject.h"

struct Entity;

class Component : public ILuaObject {
    public:
       Component();
       Component(std::string componentName, Entity* entity);

       virtual ~Component()=default;

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

       bool getActive() const { return isActive_; }
       void setActive(bool active) { isActive_ = active; }

       std::string getComponentName() const { return componentName; };

       void setComponentName(std::string name)
       {
           this->componentName = name;
       };
       
       static void ConvertToLua(lua_State* state);

    protected:
        Entity* mEntity_;
        bool isActive_;
        std::string componentName;  
};

#endif // ! COMPONENT_H


