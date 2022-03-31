#include "Entity.h"
#include "Component.h"
#include "Transform.h"
#include "../Scene/Scene.h"

Entity::Entity(Scene* node):
	mNode_(node->GetOgreNode()),active_(true),mScene_(node)
{
}

Entity::~Entity()
{
	for (Component* c : mComponentsArray_) {
		delete c;
	}
	mComponentsArray_.clear();
	mComponents_.clear();

	for (Entity* e : mChildren_) {
		delete e;
	}
	mChildren_.clear();
}

void Entity::init()
{

}

void Entity::fixedUpdate()
{
	if (active_) {
		for (auto i : mNumOfActiveComponents_) {
			mComponentsArray_[i]->fixedUpdate();
		}
		for (Entity* e : mChildren_) {
			e->fixedUpdate();
		}
	}
}

void Entity::update(float dt)
{
	if (active_) {
		for (auto i : mNumOfActiveComponents_) {
			mComponentsArray_[i]->update(dt);
		}
		for (Entity* e : mChildren_) {
			e->update(dt);
		}
	}
}

void Entity::lateUpdate()
{
	if (active_) {
		for (auto i : mNumOfActiveComponents_) {
			mComponentsArray_[i]->lateUpdate();
		}

		for (Entity* e : mChildren_) {
			e->lateUpdate();
		}
	}
}

void Entity::render()
{
	if (active_) {
		for (auto i : mNumOfActiveComponents_) {
			mComponentsArray_[i]->render();
		}

		for (Entity* e : mChildren_) {
			e->render();
		}
	}
}

Entity* Entity::addChildEntity()
{
	Ogre::SceneNode* node = mNode_->createChildSceneNode();
	Entity* e = new Entity(nullptr);

	e->setNode(node);

	mChildren_.push_back(e);

	return e;
}


void Entity::receiveEvent(Entity* receive)
{
}

bool Entity::hasComponent(unsigned int cmpID)
{
	return mComponentsArray_[cmpID] != nullptr;
}

void Entity::onCollision(Entity* other)
{
	for (auto i : mNumOfActiveComponents_) {
		mComponentsArray_[i]->onCollision(other);
	}

	for (Entity* e: mChildren_)
	{
		e->onCollision(other);
	}
}

void Entity::onTrigger(Entity* other)
{
	for (auto i : mNumOfActiveComponents_) {
		mComponentsArray_[i]->onTrigger(other);
	}

	for (Entity* e : mChildren_)
	{
		e->onTrigger(other);
	}
}

Entity* CreateEntity(Scene* scene)
{
	Entity* e = new Entity(scene);
	return e;
	
}

void Entity::ConvertToLua(lua_State* state)
{
	getGlobalNamespace(state).
		beginNamespace("ECS").
		addFunction("CreateEntity", CreateEntity).
	
		beginClass<Entity>("Entity").
			//addFunction("AddComponent", &Entity::addComponent).
			//addFunction("AddComponent", &Entity::receiveEvent).
			addFunction("isActive", &Entity::isActive).
			addFunction("setActive", &Entity::setActive).
			addFunction("getName", &Entity::getName).
			addFunction("setName", &Entity::setName).
			addFunction("getNode", &Entity::getNode).
			addFunction("getScene", &Entity::getScene).
			addFunction("setScene", &Entity::setScene).
			addFunction("receiveEvent", &Entity::receiveEvent).
			addFunction("hasComponent", &Entity::hasComponent).
			addFunction("addChildEntity", &Entity::addChildEntity).
		endClass().
		endNamespace();
}
