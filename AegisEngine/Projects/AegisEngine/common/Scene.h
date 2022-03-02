#include <list>
using namespace std;

class Entity;
class Scene
{
private:
	list<Entity*>* entities;
	list<list<Entity*>::iterator> entitiesToDelete;

	// Fixed Update arguments
	const double PHYSICS_STEP = 0.02;
	double accumulator;

	~Scene();
	void RemoveEntity(list<Entity*>::iterator entity);
	void DeletePendingEntities();
	void FixedUpdate(float dt);
	void UpdateInput();
	void Update(float dt);
	void LateUpdate(float dt);
public:
	Scene();

	void AddEntity(Entity* entity);
	void DestroyEntity(list<Entity*>::iterator entity);
	void UpdateScene(float dt);
	//void Render();
};