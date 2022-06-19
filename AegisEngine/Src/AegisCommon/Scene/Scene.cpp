#include "Scene.h"
#include "Entity.h"
#include "PhysicsMain.h"
#include "RigidbodyComponent.h"
#include "OgreWrapper.h"
#include "CameraComponent.h"
#include "Canvas.h"
using namespace luabridge;

void Scene::InitEntities() {
	for (Entity* entity : *uninitializedEntities) {
		entity->init();
	}

	uninitializedEntities->clear();
}

// Es posible que aqui queramos inicializar una escena de ogre y sincronizarla con las entidades
Scene::Scene(OgreWrapper* wrap) :
	accumulator(0), entities(new std::list<Entity*>()), entitiesToDelete(std::list<std::list<Entity*>::iterator>()) , ogreNode(wrap->GetRootNode()), uninitializedEntities(new std::list<Entity*>()),
	physicsEntities(new std::list<RigidbodyComponent*>()), ogreWrapper(wrap)
{
	mCanvas_ = new Canvas(wrap);
}

Scene::~Scene() {
	for (Entity* entity : *entities)
		delete entity;
	
	RemoveAndFreePendingEntities();

	//delete this->mCanvas_;
	delete this->entities;
	delete this->uninitializedEntities;
	delete this->physicsEntities;
}

bool Scene::Init()
{
	// Create entity with camera, default entity every scene has
	auto camera = ogreWrapper->GetCamera(); //AegisCamera* 
	Entity* cameraEntity = new Entity(this, camera->GetNode());
	cameraEntity->setName("MainCamera");
	AddEntity(cameraEntity);
	cameraEntity->addComponentFromLua(new CameraComponent(cameraEntity, camera));
	ExportToLua(cameraEntity, "MainCamera");

	return true;
}

void Scene::RemoveAndFreeEntity(std::list<Entity*>::iterator entity) {
	delete *entity; //Destroy()
	this->entities->erase(entity);
}

void Scene::RemoveAndFreePendingEntities() {
	for (std::list<Entity*>::iterator entity : entitiesToDelete)
		RemoveAndFreeEntity(entity);

	this->entitiesToDelete.clear();
}

void Scene::AddEntity(Entity* entity)
{
	this->uninitializedEntities->push_back(entity);
	this->entities->push_back(entity);
	entity->SetIterator(--entities->end());
}

void Scene::AddPhysicsEntity(RigidbodyComponent* physicsEntity)
{
	this->physicsEntities->push_back(physicsEntity);
	physicsEntity->SetIterator(--physicsEntities->end());
}

void Scene::DestroyEntity(std::list<Entity*>::iterator entity) {
	this->entitiesToDelete.push_back(entity);
}

void Scene::RemovePhysicsEntity(std::list<RigidbodyComponent*>::iterator physicsEntity)
{
	this->physicsEntities->erase(physicsEntity);
}

void Scene::FixedUpdate(float dt) {
	accumulator += dt;
	uint16_t remainingSteps = MAX_PHYSICS_STEP_PER_FRAME;

	while (accumulator >= PHYSICS_STEP && remainingSteps > 0)	{
		for(RigidbodyComponent* rb : *physicsEntities)
			rb->getEntity()->fixedUpdate();

		float timeBeforeUpdate = SDL_GetTicks();
		Physics()->update(dt, PHYSICS_STEP, 1);
		SyncTransforms();

		dt = (SDL_GetTicks() - timeBeforeUpdate) / 1000.0f;
		accumulator -= PHYSICS_STEP;
		remainingSteps--;
	}
}

void Scene::SyncTransforms()
{
	//Iterate physics entities and sync their transforms
	for (RigidbodyComponent* physicsEntity : *physicsEntities)
		physicsEntity->SyncToTransform();
	
}

void Scene::Update(float dt) {
	for (Entity* entity : *entities)
		entity->update(dt);
}

void Scene::LateUpdate(float dt) {
	for (Entity* entity : *entities)
		entity->lateUpdate(dt);
}

void Scene::UpdateScene(float dt) {
	InitEntities();
	FixedUpdate(dt);
	Update(dt);
	LateUpdate(dt);
	RemoveAndFreePendingEntities();
}

void Scene::Render()
{
	for (Entity* entity : *entities)
		entity->render();
}

void Scene::RenderUI()
{
	/*if (mCanvas_ != nullptr)
		mCanvas_->render();*/
}

//the ogreNode usually is the root scene node so we add this node as a child one
Ogre::SceneNode* Scene::GetNewNode()
{
	return ogreNode->createChildSceneNode();
}

Ogre::SceneManager* Scene::GetOgreManager()
{
	return ogreNode->getCreator();
}
void Scene::CreateCanvas()
{
	mCanvas_ = new Canvas(ogreWrapper);
}
void Scene::ConvertToLua(lua_State* state)
{
	getGlobalNamespace(state).
		beginNamespace("Aegis").
			beginClass<Scene>("Scene").
			addFunction("CreateCanvas", &Scene::CreateCanvas).
			addFunction("AddEntity", &Scene::AddEntity).
			endClass().
		endNamespace();
}
