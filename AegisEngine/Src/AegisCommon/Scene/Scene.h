#pragma once
#ifndef SCENE_H 
#define SCENE_H

#include <Ogre.h>
#include <list>
#include "ILuaObject.h"

struct Entity;
class SceneNode;
class RigidbodyComponent;
class OgreWrapper;

class Scene : public ILuaObject
{
private:
	std::list<Entity*>* entities = nullptr;
	std::list<RigidbodyComponent*>* physicsEntities = nullptr;
	std::list<Entity*>* uninitializedEntities = nullptr;
	std::list<std::list<Entity*>::iterator> entitiesToDelete;
	Ogre::SceneNode* ogreNode = nullptr;
	OgreWrapper* ogreWrapper = nullptr;
	// Fixed Update arguments

	// Este parametro quizas sea mejor a la clase application cuando la tengamos
	const double PHYSICS_STEP = 0.02; 
	const uint16_t MAX_PHYSICS_STEP_PER_FRAME = 5;
	double accumulator;

	/// <summary>
	/// Borra una entidad de la lista de entidades y ademas la destruye.
	/// Es una funcion auxiliar usada en <function>RemoveAndFreePendingEntities</function>
	/// </summary>
	/// <param name="entity">Iterador de la entidad a borrar</param>
	void removeAndFreeEntity(std::list<Entity*>::iterator entity);
	
	/// <summary>
	///  Borra y destruye todas las entidades de <param>entitiesToDelete</param>
	/// </summary>
	void removeAndFreePendingEntities();

	/// <summary>
	/// FixedUpdate se "ejecuta" cada PHYSICS_STEP (se ejecuta en el mismo hilo que lo demas). 
	/// En cada llamada a FixedUpdate, se acumula el tiempo entre frames (dt o deltaTime). Mientas este tiempo es superior a <param>PHYSICS_STEP</param>
	/// Se llama al integrate de cada entidad. Es decir, si el tiempo entre frames es muy alto, se ejecutará varias veces para "compensar" y que la simulacion 
	/// sea realista. Por el contrario, si es muy bajo es posible que no se llame todos los frames. Esto depende en parte del framerate maximo del juego y de como de pesado sea el 
	/// update. Si Framerate > PHYSICS_STEP, entonces FixedUpdate se ejecutara cada 1,25 UpdateScene (asumiento que dt siempre es igual y que Update no se pasa del tiempo de framerate).
	/// FixedUpdate no se puede ejecutar cada 1,25 UpdateScene, pero si puede hacerlo cada 2, el tiempo que sobra se acumula. En este caso y asumiendo las condiciones anteriores, 
	/// FixedUpdate se actualiza cada 2 UpdateScene, con la excepción de cada 4 UpdateScene  no se ejecuta.
	/// La tabla de ejecucion seria asi:
	/// En la ultima fila pondre el valor de acumulator antes de ejecutar FixedUpdate, asumimos que dt siempre es 0,016), en la penultima el valor despues de
	/// ejecutar FixedUpdate
	/// En el primer frame dt es 0 porque no hay frame anterior, por tanto acc es 0 tambien
	/// Update     Update                 Update             Update               Update               Update            Update                     Update       
	///                                         FixedUpdate      FixedUpdate		 FixedUpdate       FixedUpdate 	                              FixedUpdate
	///     0            0,016                 0,012                 0,008               0,004                    0			         0,016                     0,012    
	///     0            0,016                 0,032                 0,028               0,024                  0,02			     0,016                     0,032    
	/// Sincronizacion y render:
	/// No hay ningun tipo de interpolacion de movimiento actualmente, por lo que es posible que suceda esto:
	/// Consideremos esta tabla, donde las columnas representan un frame y las filas representan, en orden descendiente las funciones que se ejecutan en este
	/// Update               Update     Update             
	/// FixedUpdate       Render     FixedUpdate
	/// Es decir, por ahora y hasta que no definamos mejor el render, este podria suceder este dos fixedUpdate, lo cual daria lugar a un 
	/// movimiento como trabado, tembloroso. Hay que ver como sincronizar el render para que se ejecute cada frame y que sea despues del fixedUpdate
	/// </summary>
	void fixedUpdate(float dt);

	void syncTransforms();
	void syncRigidbodies();

	/// <summary>
	/// Llama al update de cada entidad para que actualice respectivamente sus componentes
	/// </summary>
	/// <param name="dt">deltaTime</param>
	void update(float dt);

	/// <summary>
	/// Llama al update de cada entidad para que actualice respectivamente sus componentes
	/// </summary>
	/// <param name="dt">deltaTime</param>
	void lateUpdate(float dt);

	/// <summary>
	/// Calls entity.init for every entity that has been added in the first frame
	/// This allows to call "awake" for entities that are added in runtime
	/// </summary>
	void initEntities();

	void createCamera();
public:
	Scene(OgreWrapper* wrap);

	~Scene();
	void free();
	void init();

	/// <summary>
	/// Añade una entidad ya creada a la escena. No se comprueba que la entidad sea nula en ningún momento.
	/// Añadir una entidad nula provocaria undefine behaviour o excepciones
	/// </summary>
	/// <param name="entity"></param>
	void addEntity(Entity* entity);
	Entity* instantiatePrefab(luabridge::LuaRef prefab);
	void addPhysicsEntity(RigidbodyComponent* physicsEntity);

	/// <summary>
	/// Añade un interador de entidad a la lista de entidades a destruir. La destruccion se realiza despues de lateUpdate y antes del render
	/// Usamos un interador para no tener que buscar la entidad en la lista
	/// </summary>
	/// <param name="entity"></param>
	void destroyEntity(std::list<Entity*>::iterator entity);
	void removePhysicsEntity(std::list<RigidbodyComponent*>::iterator physicsEntity);

	/// <summary>
	/// Update principal de la escena que llamar a los demas updates. El orden de ejecucion es
	/// FixedUpdate
	/// UpdateInput
	/// Update
	/// LateUpdate
	/// DeletePendingEntities
	/// Render
	/// </summary>
	/// <param name="dt"></param>
	void updateScene(float dt);
	
	void render();

	Ogre::SceneNode* getNewNode();
	Ogre::SceneManager* getOgreManager();

	static void ConvertToLua(lua_State* state);
};

#endif