#pragma once 

#ifndef _CANVAS
#define _CANVAS

#include <list>
class Entity;
class Canvas
{
private:
    std::list<Entity*> mEntitys_;
public:
    Canvas(/* args */);
    ~Canvas();

    void addEntity(Entity* ent);
    void removeEntity(Entity* ent);

    
};




#endif