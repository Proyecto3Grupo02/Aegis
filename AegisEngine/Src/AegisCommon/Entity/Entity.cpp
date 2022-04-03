#include "Entity.h"
#include "Component.h"
#include "Transform.h"
#include "../Components/Renderer.h"
#include "../Scene/Scene.h"

Entity::Entity(Scene* node) :
	mNode_(node->GetOgreNode()), active_(true), mScene_(node)
{
	//Componente obligatorio para todas las entidades
	transform = new Transform(Vector3(0,0,0), Quaternion(), Vector3(1.0f, 1.0f, 1.0f), getNode(), this);
	this->addComponentFromLua(transform);
}

Entity::Entity(Scene* node, Vector3 pos) :
	mNode_(node->GetOgreNode()), active_(true), mScene_(node)
{
	transform = new Transform(pos, Quaternion(), Vector3(1.0f, 1.0f, 1.0f), getNode(), this);
	this->addComponentFromLua(transform);
}

Entity::~Entity()
{
	for (Component* c : mComponentsArray_) {
		delete c;
	}
	mComponentsArray_.clear();
	mComponents_.clear();

	mChildren_.clear();
}

void Entity::init()
{
	for (Component* c : mComponentsArray_) {
		c->init();
	}
}

void Entity::fixedUpdate() {
	if (active_) {
		for (auto component : mComponentsArray_) {
			if (!component->getActive()) continue;
			component->fixedUpdate();
		}
	}
}

void Entity::update(float dt) {
	if (active_) {
		for (auto component : mComponentsArray_) {
			if (!component->getActive()) continue;

			component->update(dt);
		}
	}
}

void Entity::lateUpdate(float dt)
{
	if (active_) {
		for (auto component : mComponentsArray_) {
			if (!component->getActive()) continue;
			component->lateUpdate(dt);
		}
	}
}

void Entity::render() {
	if (active_) {
		for (auto component : mComponentsArray_) {
			if (!component->getActive()) continue;
			component->render();
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

void Entity::onCollision(Entity* other)
{
	for (auto component : mComponentsArray_) {
		if (!component->getActive()) continue;
		component->onCollision(other);
	}
}

void Entity::onTrigger(Entity* other)
{
	for (auto component : mComponentsArray_) {
		if (!component->getActive()) continue;
		component->onTrigger(other);
	}
}

Transform* Entity::GetTransform() const
{
	return transform;
}

void Entity::SetTransform(Transform* transform)
{
	transform->PrintErrorModifyingTables("transform", "Transform", true);
}

Entity* CreateEntity(Scene* scene, Vector3 pos)
{
	return new Entity(scene, pos);;

}

void Entity::ConvertToLua(lua_State* state)
{
	getGlobalNamespace(state).
		beginNamespace("Aegis").
		addFunction("CreateEntity", CreateEntity).

		beginClass<Entity>("Entity").
		addFunction("AddComponent", &Entity::addComponentFromLua).
		addFunction("GetComponent", &Entity::getComponentLua).
		addFunction("IsActive", &Entity::isActive).
		addFunction("SetActive", &Entity::setActive).
		addFunction("GetName", &Entity::getName).
		addFunction("SetName", &Entity::setName).
		addFunction("GetScene", &Entity::getScene).
		// No tiene sentido el setScene, no vamos a mover entidades entre escenas
		//addFunction("SetScene", &Entity::setScene).
		//addFunction("addChildEntity", &Entity::addChildEntity).
		addProperty("transform", &Entity::GetTransform, &Entity::SetTransform).
		endClass().
		endNamespace();
}