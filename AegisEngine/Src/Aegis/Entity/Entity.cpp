
#include "Entity.h"
#include "Component.h"
Entity::Entity(Ogre::SceneNode* node):
	mNode_(node),active_(true),mScene_(nullptr)
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
