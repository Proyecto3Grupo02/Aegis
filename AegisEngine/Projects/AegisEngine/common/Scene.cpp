#include "Scene.h"
#include "Entity.h"

Scene::Scene() : accumulator(0), entities(new list<Entity*>()), entitiesToDelete(list<list<Entity*>::iterator>()) {}

Scene::~Scene()
{
	for (Entity* entity : *entities)
		delete entity;

	delete this->entities;

	DeletePendingEntities();
}

void Scene::RemoveEntity(list<Entity*>::iterator entity)
{
	this->entities->erase(entity);
}

void Scene::DeletePendingEntities()
{
	for (list<Entity*>::iterator entity : entitiesToDelete)
		RemoveEntity(entity);

	this->entitiesToDelete.clear();
}

void Scene::AddEntity(Entity* entity)
{
	this->entities->push_back(entity);
}

void Scene::DestroyEntity(list<Entity*>::iterator entity)
{
	this->entitiesToDelete.push_back(entity);
}

void Scene::FixedUpdate(float dt)
{
	accumulator += dt;
	while (accumulator >= PHYSICS_STEP)
	{
		// Call entities physics update
		//for (Entity* entity : *entities)
			//entity->update();
		accumulator -= PHYSICS_STEP;
	}
}

void Scene::UpdateInput()
{
}

void Scene::Update(float dt)
{
	for (Entity* entity : *entities)
		entity->update(dt);
}

void Scene::LateUpdate(float dt)
{
	for (Entity* entity : *entities)
		entity->lateUpdate();
}

void Scene::UpdateScene(float dt)
{
	// Esto hay que moverlo al update de la aplicacion, por ahora esta aqui
	// Es decir, en caso de que el update scene se complete mas rapido de lo esperado
	// Hay que esperar antes del siguiente update
	//double current = getCurrentTime();
	//double elapsed = current - previousFrameTime;
	//previousFrameTime = current;

	FixedUpdate(dt);
	UpdateInput();
	Update(dt);
	LateUpdate(dt);
	//Render;
}
