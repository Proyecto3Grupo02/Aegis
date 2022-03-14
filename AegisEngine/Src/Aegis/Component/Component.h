#pragma once
#ifndef  COMPONENT_H 
#define COMPONENT_H

#include <Ogre.h>

namespace AegisEngine {
    class Entity;

    class Component {
    public:
        Component();

        ~Component() {};

        inline Entity* getEntity() { return mEntity_; }
        void setEntity(Entity* entity) { mEntity_ = entity; }

        virtual void init() = 0;

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
}
#endif // ! COMPONENT_H


