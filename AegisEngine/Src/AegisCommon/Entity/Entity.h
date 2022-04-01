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
	void lateUpdate(float dt);

	void render();

	inline bool isActive() { return active_; }
	inline void setActive(bool act) { active_ = act; }

	inline std::string getName() { return mName_; }
	inline void setName(std::string name) { mName_ = name; }


	inline Ogre::SceneNode* getNode() { return mNode_; }
	inline void setNode(Ogre::SceneNode* node) { mNode_ = node; }
	Entity* addChildEntity();

	//handle the components

	inline void addComponentFromLua(AegisComponent* component) {
		std::string key = component->GetComponentName();

		if (mComponents_.find(key) == mComponents_.end()) { //si no está lo añadimos
			component->setEntity(this);

			mComponentsArray_.push_back(component);
			mComponents_[key] = component;
		}
	}

	template <class T, class...Targs>
	inline T* addComponent(const char* name, Targs&&...args)
	{
		//SOLUCIÓN PROVISIONAL EN LA QUE HAY QUE PASAR COMO PARÁMETRO EL NOMBRE DEL COMPONENTE,
		//DEBERÍA DE FUNCIONAR CON EL KEY DE ENCIMA DE ESTE COMENTARIO
		auto key = name;

		if (mComponents_.find(key) == mComponents_.end()) { //si no está lo añadimos
			T* t = (new T(std::forward<Targs>(args)...));
			t->setEntity(this);

			mComponentsArray_.push_back(t);
			mComponents_[key] = static_cast<AegisComponent*>(t);
			return (T*)mComponents_[key];
		}

		return nullptr;
	}

	inline AegisComponent* getComponentLua(std::string componentName)
	{
		if (mComponents_.count(componentName) == 0)
			return nullptr;
		else return  mComponents_[componentName];
	}

	template <typename T>
	inline T* getComponent(const char* componentName)
	{
		return dynamic_cast<T*>(getComponentLua(componentName));
	}

	inline Scene* getScene() { return mScene_; }
	inline void setScene(Scene* scene) { mScene_ = scene; }
	//doubt
	void receiveEvent(Entity* receive);
	bool hasComponent(unsigned int cmpID);
	void onCollision(Entity* other);
	void onTrigger(Entity* other);

	Transform* GetTransform() const;
	void SetTransform(Transform* transform);

	static void ConvertToLua(lua_State* state);

	Ogre::SceneNode* GetNode();
protected:
	Scene* mScene_; //scene pointer 
	std::unordered_map <std::string, AegisComponent*> mComponents_; //list of all the components in scene
	std::vector<AegisComponent*> mComponentsArray_; //list of all the components in scene
	bool active_; //bool to check if the entity is active or not

	Ogre::SceneNode* mNode_;

	std::list<Entity*> mChildren_;


private:
	std::string mName_; //name of the entity, works like a tag, useful to debug
	Transform* transform;

};

#endif //