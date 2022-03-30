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
	}
}

void Entity::update(float dt)
{
	if (active_) {
		for (auto i : mNumOfActiveComponents_) {
			mComponentsArray_[i]->update(dt);
		}
	}
}

void Entity::lateUpdate()
{
	if (active_) {
		for (auto i : mNumOfActiveComponents_) {
			mComponentsArray_[i]->lateUpdate();
		}
	}
}

void Entity::render()
{
	if (active_) {
		for (auto i : mNumOfActiveComponents_) {
			mComponentsArray_[i]->render();
		}
	}
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
}

void Entity::onTrigger(Entity* other)
{
	for (auto i : mNumOfActiveComponents_) {
		mComponentsArray_[i]->onTrigger(other);
	}
}

Entity* CreateEntity(Scene* scene)
{
	return new Entity(scene);
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
		endClass().
		endNamespace();
}
