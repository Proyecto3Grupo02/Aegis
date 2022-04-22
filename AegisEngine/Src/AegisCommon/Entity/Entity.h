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
#include "../../checkML.h"

namespace Ogre {
    class SceneNode;
}

class Component;
class Transform;
class Scene;
struct Vector3;

struct Entity : public ILuaObject {
public:
	Entity(Scene* scene);
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
	inline void setNode(Ogre::SceneNode* node) { mNode_ = node; }

	inline void addComponentFromLua(AegisComponent* component);
	AegisComponent* getComponentLua(std::string componentName);

	template <typename T>
	inline T* getComponent(const char* componentName);

	inline Scene* getScene() { return mScene_; }
	inline void setScene(Scene* scene) { mScene_ = scene; }
	void SetIterator(std::list<Entity*>::iterator entityIterator);

	//doubt
	void onCollision(Entity* other);
	void onTrigger(Entity* other);

	Transform* GetTransform() const;
	void SetTransform(Transform* transform);
	void SetParent(Entity* ent);

	void Destroy();

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
	std::list<Entity*>::iterator entityIterator;
};

#endif //
