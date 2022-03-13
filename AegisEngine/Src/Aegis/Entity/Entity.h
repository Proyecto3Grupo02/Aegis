
#pragma once 
#include <vector>
#include <list>
#include <string>
#include "ComponentManager.h"
#include <Ogre.h>
#include "Transform.h"


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
        inline void setName(std::string name) { mName_ = name; }


        inline Ogre::SceneNode* getNode() { return mNode_; }

        //handle the components
       
        template<typename T, typename...Targs>
        inline T* addComponent(std::string name, Targs&&...args)
        {
            ComponentManager* mngr = ComponentManager::getInstance();
            if (mngr != nullptr) {
                //std::string key = mngr->GetID<T>(); //cuando un component esta registrado  pilla su id de ahi

                //SOLUCIÓN PROVISIONAL EN LA QUE HAY QUE PASAR COMO PARÁMETRO EL NOMBRE DEL COMPONENTE,
                //DEBERÍA DE FUNCIONAR CON EL KEY DE ENCIMA DE ESTE COMENTARIO
                std::string key = name;

                if (mComponents_.find(key) == mComponents_.end()) { //si no está lo añadimos
                    T* t = (new T(std::forward<Targs>(args)...));
                    t->setEntity(this);
                    mComponentsArray_.push_back(t);
                    mComponents_[key] = t;
                    t->init();
                    return (T*)mComponents_[key];

                }

            }
            return nullptr;
        }

        template<typename T>
        inline T* getComponent()
        {
            ComponentManager* cmpManager = ComponentManager::getInstance();

            std::string id = cmpManager->GetID<T>();

            return (T*)mComponents_[id];
        }

        inline Scene* getScene(){return mScene_;}
        inline void setScene(Scene* scene){mScene_= scene;}
        //doubt
        void receiveEvent(Entity* receive);
        bool hasComponent(unsigned int cmpID);
        void onCollision(Entity* other); 
        void onTrigger(Entity* other);


    protected:
        Scene* mScene_; //scene pointer 
        std::map<std::string, Component*> mComponents_; //list of all the components in scene
       std::vector<Component*> mComponentsArray_; //list of all the components in scene
        std::list<int> mNumOfActiveComponents_; //list of the index of their active component 
        bool active_; //bool to check if the entity is active or not

        Ogre::SceneNode* mNode_;


    private:
        std::string mName_; //name of the entity, works like a tag, useful to debug


};

