#pragma once

#ifndef ENTITY_H 
#define ENTITY_H

#include <Ogre.h>
#include <vector>
#include <list>
#include <string>

#include "AegisComponent.h"
#include "ILuaObject.h"
//#include "../../checkML.h"

namespace Ogre {
    class SceneNode;
}

class Component;
class TransformComponent;
class Scene;
struct Vector3;

struct Entity : public ILuaObject {
public:
	Entity(Scene* scene, Ogre::SceneNode* node = nullptr);
	Entity(Scene* scene, Vector3 pos);
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

	void destroyNode();
	void detachChildren();
	void removeAllComponents();
	inline void addComponentFromLua(AegisComponent* component);
	AegisComponent* getComponentLua(std::string componentName);

	template <typename T>
	inline T* getComponent(const char* componentName);

	inline Scene* getScene() { return mScene_; }
	inline void setScene(Scene* scene) { mScene_ = scene; }
	void setIterator(std::list<Entity*>::iterator entityIterator);

	//doubt
	void onCollision(Entity* other);
	void onTrigger(Entity* other);

	TransformComponent* getTransform() const;
	void setTransform(TransformComponent* transform);
	void setParent(Entity* ent);

	void destroy();
	void setNodeDestroyedOrBlocked(bool isDestroyed) { nodeDestroyedOrBlocked = isDestroyed;  };

	static void ConvertToLua(lua_State* state);

protected:
	Scene* mScene_ = nullptr; //scene pointer 
	std::unordered_map <std::string, AegisComponent*> mComponents_; //list of all the components in scene
	std::vector<AegisComponent*> mComponentsArray_; //list of all the components in scene
	bool active_; //bool to check if the entity is active or not

	Ogre::SceneNode* mNode_ = nullptr;

private:
	std::string mName_;			//name of the entity
	TransformComponent* transform;		//native transform
	std::list<Entity*>::iterator entityIterator;
	bool nodeDestroyedOrBlocked;
};

#endif //
