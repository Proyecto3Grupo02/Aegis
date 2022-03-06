#pragma once 
#include <vector>
#include <list>
#include <string>
#include "ComponentManager.h"
#include <Ogre.h>


class Component;
class Scene;
class Entity{
    public:
        Entity(Ogre::SceneNode* node);
        ~Entity();

        void init();
       
        void fixedUpdate();
        void update(float dt);
        void lateUpdate();

        void render();

        inline bool isActive(){return active_;}
        inline void setActive(bool act){active_=act;}

        
        inline std::string getName(){return mName_;}
        inline void setName(std::string name){}

        //handle the components
       
        template<typename T>
        T* addComponent();

        template<typename T>
        T* getComponent();

        inline Scene* getScene(){return mScene_;}
        inline void setScene(Scene* scene){mScene_= scene;}
        //doubt
        void receiveEvent(Entity* receive);
        bool hasComponent(unsigned int cmpID);
        void onCollision(Entity* other); 
        void onTrigger(Entity* other);


    protected:
        Scene* mScene_; //scene pointer 
        std::vector<Component*> mComponents_; //list of all the components in scene
        std::list<int> mNumOfActiveComponents_; //list of the index of their active component 
        bool active_; //bool to check if the entity is active or not

        Ogre::SceneNode* mNode_;


    private:
        std::string mName_; //name of the entity, works like a tag, useful to debug


};

