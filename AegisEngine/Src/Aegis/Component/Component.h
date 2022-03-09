#pragma once
#include <string>
#include <Ogre.h>

class Entity;

class Component{
    public:
       Component(Entity* entity);

       ~Component() {};

       inline Entity* getEntity() { return mEntity_; }

       virtual void init()=0;
       
       virtual void fixedUpdate() {};
       virtual void update(float dt) {};
       virtual void lateUpdate() {};
     
       virtual void render() {};

       virtual void onCollision(Entity* other) {};
       virtual void onTrigger(Entity* other) {};

       bool getActive() { return isActive_; }
       void setActive(bool active) { isActive_ = active; }
    private:
        Entity* mEntity_;
        bool isActive_;
        
};


