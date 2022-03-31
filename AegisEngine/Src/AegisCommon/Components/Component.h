#pragma once
#ifndef  COMPONENT_H 
#define COMPONENT_H

#include <Ogre.h>
#include "../Interfaces/ILuaObject.h"

class Entity;

class Component : public ILuaObject {
    public:
       Component();

       ~Component() {};

       inline Entity* getEntity() { return mEntity_; }
       void setEntity(Entity* entity) { mEntity_ = entity; }

       virtual void init()=0;
       
       virtual void fixedUpdate() {};
       virtual void update(float dt) {};
       virtual void lateUpdate() {};
     
       virtual void render() {};

       virtual void onCollision(Entity* other) {};
       virtual void onTrigger(Entity* other) {};

       bool getActive() { return isActive_; }
       void setActive(bool active) { isActive_ = active; }

       std::string GetComponentName() const { return componentName; };
       void SetComponentName(std::string name) { componentName = name; };

       Entity* GetEntity() const 
       { 
           return mEntity_; 
       };
       void SetEntity(Entity* entity) { mEntity_ = entity; };
       
       static void ConvertToLua(lua_State* state);
    private:
        Entity* mEntity_;
        bool isActive_;
        std::string componentName;
        
};

#endif // ! COMPONENT_H


