#pragma once
#ifndef ENTITY_H 
#define ENTITY_H

#include <vector>
#include <list>
#include <string>
#include "../Managers/ComponentManager.h"
#include "../Components/AegisComponent.h"
#include <Ogre.h>
#include "../Interfaces/ILuaObject.h"

class Component;
class Transform;
class Scene;

struct Entity : public ILuaObject {
    public:
        Entity(Scene* node);
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
        inline void setNode(Ogre::SceneNode* node) { mNode_ = node; }
        Entity* addChildEntity();

        //handle the components
       
        inline void addComponentFromLua(AegisComponent* component) {
            ComponentManager* mngr = ComponentManager::getInstance();
            if (mngr != nullptr) {
                std::string key = component->GetComponentName();

                if (mComponents_.find(key) == mComponents_.end()) { //si no está lo añadimos
                    component->setEntity(this);

                    mComponentsArray_.push_back(component);
                    mComponents_[key] = component;
                }
            }
        }

        template <class T, class...Targs>
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

        static void ConvertToLua(lua_State* state);
    protected:
        Scene* mScene_; //scene pointer 
        std::map<std::string, AegisComponent*> mComponents_; //list of all the components in scene
        std::vector<AegisComponent*> mComponentsArray_; //list of all the components in scene
        bool active_; //bool to check if the entity is active or not

        Ogre::SceneNode* mNode_;

        std::list<Entity*> mChildren_;


    private:
        std::string mName_; //name of the entity, works like a tag, useful to debug


};

#endif //