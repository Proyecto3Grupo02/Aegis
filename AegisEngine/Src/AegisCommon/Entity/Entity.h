#pragma once
#ifndef ENTITY_H 
#define ENTITY_H



#include "../Managers/ComponentManager.h"

#include <vector>
#include <list>
#include <string>
#include "../Managers/ComponentManager.h"
#include "../Components/AegisComponent.h"
#include <Ogre.h>
#include "../Interfaces/ILuaObject.h"

namespace Ogre {
    class SceneNode;
}

class Component;
class Transform;
class Scene;
struct Vector3;

struct Entity : public ILuaObject {
public:
	Entity(Scene* node);
	Entity(Scene* node, Vector3 pos);
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

	inline void addComponentFromLua(AegisComponent* component) {
		std::string key = component->GetComponentName();

		if (mComponents_.count(key) == 0) { //si no est� lo a�adimos
			//component->SetEntity(this);

			mComponentsArray_.push_back(component);
			mComponents_[key] = component;
		}
		else
		 {
			std::cout << key << " is already in " << mName_ << ", component will be deleted";
			delete component;
		}
	}

	AegisComponent* getComponentLua(std::string componentName)
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
	void onCollision(Entity* other);
	void onTrigger(Entity* other);

	Transform* GetTransform() const;
	void SetTransform(Transform* transform);

	static void ConvertToLua(lua_State* state);
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