#include "Entity.h"
#include "Component.h"
Entity::Entity(): 
	mNumOfComponents_(0),active_(true),mScene_(nullptr)
{
}

Entity::~Entity()
{
}

void Entity::init()
{

}

void Entity::fixedUpdate()
{
	for (auto i : mNumOfActiveComponents_) {
		mComponents_[i]->fixedUpdate();
	}
}

void Entity::update(float dt)
{
	for (auto i : mNumOfActiveComponents_) {
		mComponents_[i]->update(dt);
	}
}

void Entity::lateUpdate()
{
	for (auto i : mNumOfActiveComponents_) {
		mComponents_[i]->lateUpdate();
	}
}

void Entity::render()
{
	for (auto i : mNumOfActiveComponents_) {
		mComponents_[i]->render();
	}
}

Component* Entity::getComponent(unsigned int cmpID)
{
	return mComponents_[cmpID];
}

void Entity::receiveEvent(Entity* receive)
{
}

bool Entity::hasComponent(unsigned int cmpID)
{
	return mComponents_[cmpID] != nullptr;
}

void Entity::onCollision(Entity* other)
{
	for (auto i : mNumOfActiveComponents_) {
		mComponents_[i]->onCollision(other);
	}
}

void Entity::onTrigger(Entity* other)
{
	for (auto i : mNumOfActiveComponents_) {
		mComponents_[i]->onTrigger();
	}
}
	