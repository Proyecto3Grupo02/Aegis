#include "Entity.h"
#include "Component.h"
#include "Transform.h"
#include "../Components/Renderer.h"
#include "../Scene/Scene.h"

Entity::Entity(Scene* node) :
	mNode_(node->GetOgreNode()), active_(true), mScene_(node)
{
	//Componente obligatorio para todas las entidades
	transform = this->addComponent<Transform>("Transform", Vector3(0,0,0), Vector4(), Vector3(1.0f, 1.0f, 1.0f));
	
	// TEMPORAL
	auto r = new Renderer(this, "fish.mesh", mNode_->getCreator());
	this->addComponentFromLua(r);
}

Entity::~Entity()
{
	for (Component* c : mComponentsArray_) {
		delete c;
	}
	mComponentsArray_.clear();
	mComponents_.clear();

	//for (Entity* e : mChildren_) {
	//	delete e;
	//}
	mChildren_.clear();
}

void Entity::init()
{

}

void Entity::fixedUpdate()
{
	if (active_) {
		for (auto component : mComponentsArray_) {
			if (!component->getActive()) continue;
			component->fixedUpdate();
		}
		/*	for (Entity* e : mChildren_) {
				e->fixedUpdate();
			}*/
	}
}

void Entity::update(float dt)
{
	if (active_) {
		for (auto component : mComponentsArray_) {
			if (!component->getActive()) continue;

			component->update(dt);
		}
		/*for (Entity* e : mChildren_) {
			e->update(dt);
		}*/
	}
}

void Entity::lateUpdate()
{
	if (active_) {
		for (auto component : mComponentsArray_) {
			if (!component->getActive()) continue;
			component->lateUpdate();
		}

		/*	for (Entity* e : mChildren_) {
				e->lateUpdate();
			}*/
	}
}

void Entity::render()
{
	if (active_) {
		for (auto component : mComponentsArray_) {
			if (!component->getActive()) continue;
			component->render();
		}

		/*for (Entity* e : mChildren_) {
			e->render();
		}*/
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
	for (auto component : mComponentsArray_) {
		if (!component->getActive()) continue;
		component->onCollision(other);
	}

	//for (Entity* e: mChildren_)
	//{
	//	e->onCollision(other);
	//}
}

void Entity::onTrigger(Entity* other)
{
	for (auto component : mComponentsArray_) {
		if (!component->getActive()) continue;
		component->onTrigger(other);
	}

	//for (Entity* e : mChildren_)
	//{
	//	e->onTrigger(other);
	//}
}

Transform* Entity::GetTransform() const
{
	return transform;
}

void Entity::SetTransform(Transform* transform)
{
	this->transform = transform;
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
		addFunction("AddComponent", &Entity::addComponentFromLua).
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
		addFunction("getTransform", &Entity::GetTransform).
		addProperty("transform", &Entity::GetTransform, &Entity::SetTransform).
		endClass().
		endNamespace();
}
