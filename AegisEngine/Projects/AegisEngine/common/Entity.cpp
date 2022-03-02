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

void Entity::update()
{
	for (auto i : mNumOfActiveComponents_) {
		mComponents_[i]->update();
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

void Entity::addComponent(Component* component)
{
	component->setID(mNumOfComponents_);
	mComponents_.push_back(component);
	component->init();
	
	mNumOfComponents_++;
}

void Entity::removeComponent(unsigned int componentId)
{
	delete mComponents_[componentId];
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
	