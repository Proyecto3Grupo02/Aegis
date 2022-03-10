
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

template<typename T, typename...Targs>
inline T* Entity::addComponent(Targs&&...args)
{
	ComponentManager* mngr = ComponentManager::getInstance();
	if (mngr != nullptr) {
		std::string key = mngr->GetID<T>(); //cuando un component esta registrado  pilla su id de ahi

		if (mComponents_.find(key) == mComponents_.end()) { //si no está lo añadimos
			T* t = (new T(std::forward<Targs>(args)...));
			t->setEntity(this);
			
			mComponentsArray_.push_back(t);
			mComponents_[key] = t;
			return (T*)mComponents_[key];

		}

	}
	return nullptr;
}

template<typename T>
T* Entity::getComponent()
{
	ComponentManager* cmpManager = ComponentManager::getInstance();

	std::string id = cmpManager->GetID<T>();

	return T* mComponents_[id];
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
