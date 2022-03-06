#pragma once

class Entity;

class Component{
    public:
       Component(Entity* entity);

       ~Component() {};

       inline Entity* getEntity() { return mEntity_; }

       virtual void init()=0;
       
       virtual void fixedUpdate() = 0;
       virtual void update(float dt)=0;
       virtual void lateUpdate()=0;
     
       virtual void render() = 0;

       virtual void onCollision(Entity* other)=0;
       virtual void onTrigger(Entity* other)=0;

       bool getActive() { return isActive_; }
       void setActive(bool active) { isActive_ = active; }
    private:
        Entity* mEntity_;
        bool isActive_;
        
};


