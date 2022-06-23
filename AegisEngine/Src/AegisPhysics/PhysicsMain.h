#pragma once
#ifndef PHYSICS_MAIN_H 
#define PHYSICS_MAIN_H

#include <vector>
#include "Singleton.h"
#include "Rigidbody.h"
#include <map>

class btDiscreteDynamicsWorld;
class btDefaultCollisionConfiguration;
class btCollisionDispatcher;
class btBroadphaseInterface;
class btSequentialImpulseConstraintSolver;
class btCollisionShape;
class btCollisionObject;
//class btBulletWorldImporter;

class Vector3;
class Transform;
class btTransform;
class btVector3;
class Entity;
class RigidbodyComponent;
class OgreDebugDrawer;

#define PhysicsSys PhysicsSystem::getInstance()

namespace Ogre {
	class SceneManager;
}

class PhysicsSystem : public  Singleton<PhysicsSystem> {

private:
	//btDiscreteDynamicsWorld* dynamicsWorld;
	btDefaultCollisionConfiguration* collisionConfiguration;
	btCollisionDispatcher* dispatcher;
	btBroadphaseInterface* overlappingPairCache;
	btSequentialImpulseConstraintSolver* solver;
	Ogre::SceneManager* scene = nullptr;

	std::map<std::pair<RigidBody*, RigidBody*>, bool> contacts;
	//btBulletWorldImporter* fileLoader;

	OgreDebugDrawer* mDebugDrawer;
public:
	PhysicsSystem(Ogre::SceneManager* mScene);
	~PhysicsSystem();
	btDiscreteDynamicsWorld* dynamicsWorld;
	void update(float timeStep, float fixedTimeStep, int maxSteps = 1);
	void remove();
	void removeRigidbody(btCollisionObject* rb);
	btTransform parseToBulletTransform(Vector3 pos, Vector3 rot);
	btTransform parseToBulletTransform(Vector3 pos, Vector4 rot);
	btRigidBody* createRigidBody(RigidBody::RigidBodyType rbType, float _mass, Vector3 _dim, Vector3 _pos, Vector4 rotation, std::string bodyMeshName = "", bool isConvex = true, bool isKinematic = false, bool useGravity = true);

	const btVector3 parseToBulletVector(const Vector3& v) const;
	const Vector3 parseFromBulletVector(const btVector3& v) const;

	//std::vector<Vector3> getVertexFromMesh(std::string meshName);
	//btCollisionShape* createShapeWithVertices(Vector3 _dim, std::string bodyMeshName, bool isConvex);
	btCollisionShape* createBodyShape(RigidBody::RigidBodyType rbType, Vector3 _dim, std::string bodyMeshName, bool isConvex);
	void clear();

	void checkCollision();
	void CollisionEnterCallbacks(std::pair<RigidBody*, RigidBody*>& col);
	void CollisionExitCallbacks(std::pair<RigidBody*, RigidBody*>& col);


};

#endif