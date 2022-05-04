#include "Entity.h"
#include "Component.h"
#include "Transform.h"
#include "../Components/Renderer.h"
#include "../Scene/Scene.h"

Entity::Entity(Scene* scene, Ogre::SceneNode* node) :
	mNode_(node == nullptr ?  scene->GetNewNode() : node), active_(true), mScene_(scene)
{
	//Componente obligatorio para todas las entidades
	transform = new Transform(Vector3(0,0,0), Ogre::Quaternion(), Vector3(1.0f, 1.0f, 1.0f), getNode(), this);
	this->addComponentFromLua(transform);
}


Entity::Entity(Scene* scene, Vector3 pos) :
	mNode_(scene->GetNewNode()), active_(true), mScene_(scene)
{
	transform = new Transform(pos, Ogre::Quaternion(), Vector3(1.0f, 1.0f, 1.0f), getNode(), this);
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
	
	DestroyNode();
}

template<typename T>
inline T* Entity::getComponent(const char* componentName)
{
	return dynamic_cast<T*>(getComponentLua(componentName));
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

void Entity::DestroyNode()
{
	//Node can be null if a parent destroys a child before the child destroys itself
	auto mParent = mNode_ == nullptr ? nullptr : mNode_->getParentSceneNode();
	if (mParent != nullptr)
		mParent->removeAndDestroyChild(mNode_);
	 }

inline void Entity::addComponentFromLua(AegisComponent* component)
{
	std::string key = component->GetComponentName();

	if (mComponents_.count(key) == 0) { //si no est� lo a�adimos
		//component->SetEntity(this);

		mComponentsArray_.push_back(component);
		mComponents_[key] = component;
	}
	else
	{
		std::cout << key << " is already in " << mName_ << ", component will be deleted";
		delete component;
	}
}

AegisComponent* Entity::getComponentLua(std::string componentName)
{
	if (mComponents_.count(componentName) == 0)
		return nullptr;
	else return  mComponents_[componentName];
}

void Entity::SetIterator(std::list<Entity*>::iterator entityIterator)
{
	this->entityIterator = entityIterator;
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

void Entity::SetParent(Entity* ent)
{
	if (transform != nullptr)
		transform->SetParent(ent);
	else
		std::cout << "ERROR: For some reason transform is null in entity " << getName() << "\n";
}

void Entity::Destroy()
{
	GetTransform()->DestroyChilds();
	mScene_->DestroyEntity(entityIterator);
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
		addFunction("SetParent", &Entity::SetParent).
		addFunction("Destroy", &Entity::Destroy).
		addProperty("transform", &Entity::GetTransform, &Entity::SetTransform).
		endClass().
		endNamespace();
}