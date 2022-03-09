
#include "Entity.h"
#include "Component.h"
Entity::Entity(Ogre::SceneNode* node):
	mNode_(node),active_(true),mScene_(nullptr)
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
	if (active_) {
		for (auto i : mNumOfActiveComponents_) {
			mComponents_[i]->fixedUpdate();
		}
	}
}

void Entity::update(float dt)
{
	if (active_) {
		for (auto i : mNumOfActiveComponents_) {
			mComponents_[i]->update(dt);
		}
	}
}

void Entity::lateUpdate()
{
	if (active_) {
		for (auto i : mNumOfActiveComponents_) {
			mComponents_[i]->lateUpdate();
		}
	}
}

void Entity::render()
{
	if (active_) {
		for (auto i : mNumOfActiveComponents_) {
			mComponents_[i]->render();
		}
	}
}

template<typename floa>
inline floa* Entity::addComponent()
{
	ComponentManager* cmpManager = ComponentManager::getInstance();

	std::string id = cmpManager->getCmpID<floa>();
	auto constructor = cmpManager->getCmpFactory(id);
	mComponents_[id] = constructor(this);

	return (floa*)mComponents_[id];

}

template<typename T>
T* Entity::getComponent()
{
	ComponentManager* cmpManager = ComponentManager::getInstance();

	std::string id = cmpManager->getCmpID<T>();

	return T* mComponents_[id];
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
		mComponents_[i]->onTrigger(other);
	}
}
