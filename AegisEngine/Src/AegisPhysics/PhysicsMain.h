#pragma once
#ifndef PHYSICS_MAIN_H 
#define PHYSICS_MAIN_H

#include <vector>
#include "../AegisCommon/Utils/Singleton.h"
#include "Rigidbody.h"

class btDiscreteDynamicsWorld;
class btDefaultCollisionConfiguration;
class btCollisionDispatcher;
class btBroadphaseInterface;
class btSequentialImpulseConstraintSolver;
class btCollisionShape;
class btCollisionObject;
class btBulletWorldImporter;

class Vector3;
class Transform;
class btTransform;
class btVector3;

class PhysicsSystem  : public  Singleton<PhysicsSystem>{

private:
    btDiscreteDynamicsWorld* dynamicsWorld;
    btDefaultCollisionConfiguration* collisionConfiguration;
    btCollisionDispatcher* dispatcher;
    btBroadphaseInterface* overlappingPairCache;
    btSequentialImpulseConstraintSolver* solver;
    btBulletWorldImporter* fileLoader;
public:
    PhysicsSystem();
    ~PhysicsSystem();


    void Init();
    void update();
    void remove();
    void removeRigidbody(btCollisionObject* rb);
    btTransform parseToBulletTransform(Vector3 pos, Vector3 rot);
    btTransform parseToBulletTransform(Vector3 pos, Vector4 rot);
    btRigidBody* createRigidBody(RigidBody::RigidBodyType rbType, float _mass, Vector3 _dim, Vector3 _pos, std::string bodyMeshName = "", bool isConvex = true, bool isKinematic = false);
      
    const btVector3 parseToBulletVector(const Vector3& v) const;
    const Vector3 parseFromBulletVector(const btVector3& v) const;

    //std::vector<Vector3> getVertexFromMesh(std::string meshName);
    //btCollisionShape* createShapeWithVertices(Vector3 _dim, std::string bodyMeshName, bool isConvex);
    btCollisionShape* createBodyShape(RigidBody::RigidBodyType rbType, Vector3 _dim, std::string bodyMeshName, bool isConvex);
    
    void clear();
};

inline PhysicsSystem* Physics()
{
    return PhysicsSystem::getInstance();
}

#endif