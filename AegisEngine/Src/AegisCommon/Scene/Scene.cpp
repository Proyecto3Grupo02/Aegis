#include "Scene.h"
#include "Entity.h"
#include "PhysicsMain.h"
#include "RigidbodyComponent.h"
#include "OgreWrapper.h"
#include "CameraComponent.h"

void Scene::initEntities() {
	for (Entity* entity : *uninitializedEntities) {
		entity->init();
	}

	uninitializedEntities->clear();
}

// Es posible que aqui queramos inicializar una escena de ogre y sincronizarla con las entidades
Scene::Scene(OgreWrapper* wrap) :
	accumulator(0), entities(new std::list<Entity*>()), entitiesToDelete(std::list<std::list<Entity*>::iterator>()), ogreNode(wrap->getRootNode()), uninitializedEntities(new std::list<Entity*>()),
	physicsEntities(new std::list<RigidbodyComponent*>()), ogreWrapper(wrap)
{}

Scene::~Scene() {
	free();

	if (entities)
		delete this->entities;
	if (uninitializedEntities)
		delete this->uninitializedEntities;
	if (physicsEntities)
		delete this->physicsEntities;

	this->entities = nullptr;
	this->uninitializedEntities = nullptr;
	this->physicsEntities = nullptr;
}

void Scene::free()
{
	for (Entity* entity : *entities) {
		delete entity;
		entity = nullptr;
	}

	entities->clear();
	physicsEntities->clear();
	entitiesToDelete.clear();
	uninitializedEntities->clear();
}

void Scene::init()
{
	createCamera();
}

void Scene::createCamera()
{
	Entity* cameraEntity = new Entity(this, ogreWrapper->getCamera()->getNode());
	cameraEntity->setName("MainCamera");
	cameraEntity->setNodeDestroyedOrBlocked(true);
	cameraEntity->addComponentFromLua(new CameraComponent(cameraEntity, ogreWrapper->getCamera()));
	addEntity(cameraEntity);
	exportToLua(cameraEntity, "MainCamera");
}

void Scene::removeAndFreeEntity(std::list<Entity*>::iterator entity) {
	delete* entity; //Destroy()
	this->entities->erase(entity);
}

void Scene::removeAndFreePendingEntities() {
	for (std::list<Entity*>::iterator entity : entitiesToDelete)
		removeAndFreeEntity(entity);

	this->entitiesToDelete.clear();
}

void Scene::addEntity(Entity* entity)
{
	this->uninitializedEntities->push_back(entity);
	this->entities->push_back(entity);
	entity->setIterator(--entities->end());
}

void Scene::instantiatePrefab(luabridge::LuaRef prefab)
{
	luabridge::LuaRef luaUtils = getGlobal(prefab.state(), "utils");
	luaUtils["ParseEntity"](prefab);
}

void Scene::addPhysicsEntity(RigidbodyComponent* physicsEntity)
{
	this->physicsEntities->push_back(physicsEntity);
	physicsEntity->setIterator(--physicsEntities->end());
}

void Scene::destroyEntity(std::list<Entity*>::iterator entity) {
	this->entitiesToDelete.push_back(entity);
}

void Scene::removePhysicsEntity(std::list<RigidbodyComponent*>::iterator physicsEntity)
{
	this->physicsEntities->erase(physicsEntity);
}

void Scene::fixedUpdate(float dt) {
	accumulator += dt;

	if (accumulator >= PHYSICS_STEP) {
		for (RigidbodyComponent* rb : *physicsEntities)
			rb->getEntity()->fixedUpdate();

		PhysicsSystem::getInstance()->update(dt, PHYSICS_STEP, MAX_PHYSICS_STEP_PER_FRAME);

		accumulator -= PHYSICS_STEP;
	}

	syncTransforms();
}

void Scene::syncTransforms()
{
	//Iterate physics entities and sync their transforms
	for (RigidbodyComponent* physicsEntity : *physicsEntities)
		physicsEntity->syncTransformToRigidbody();
}

void Scene::syncRigidbodies()
{
	for (RigidbodyComponent* physicsEntity : *physicsEntities)
		physicsEntity->syncRigidbodyToTransform();
}

void Scene::update(float dt) {
	for (Entity* entity : *entities)
		entity->update(dt);
}

void Scene::lateUpdate(float dt) {
	for (Entity* entity : *entities)
		entity->lateUpdate(dt);
}

void Scene::updateScene(float dt) {
	initEntities();
	fixedUpdate(dt);
	update(dt);
	lateUpdate(dt);
	syncRigidbodies();
	removeAndFreePendingEntities();
}

void Scene::render()
{
	for (Entity* entity : *entities)
		entity->render();
}

//the ogreNode usually is the root scene node so we add this node as a child one
Ogre::SceneNode* Scene::getNewNode()
{
	return ogreNode->createChildSceneNode();
}

Ogre::SceneManager* Scene::getOgreManager()
{
	return ogreNode->getCreator();
}

void Scene::ConvertToLua(lua_State* state)
{
	getGlobalNamespace(state).
		beginNamespace("Aegis").
		beginClass<Scene>("Scene").
		addFunction("AddEntity", &Scene::addEntity).
		addFunction("InstantiatePrefab", &Scene::instantiatePrefab).
		endClass().
		endNamespace();
}
