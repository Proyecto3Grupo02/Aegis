#pragma once

class btDiscreteDynamicsWorld;
class btDefaultCollisionConfiguration;
class btCollisionDispatcher;
class btBroadphaseInterface;
class btSequentialImpulseConstraintSolver;
class btCollisionShape;
#include <vector>
#include "../AegisCommon/Utils/Singleton.h"
#include "Rigidbody.h"
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

    std::vector<btCollisionShape*> collisionShapes;

public:
    PhysicsSystem();
    ~PhysicsSystem();

    btRigidBody* createRigidBody(RigidBody::RigidBodyType rbType, float _mass, Vector3 _dim, Vector3 _pos, std::string bodyMeshName = "", bool isConvex = true);

    void Init();
    void update();
    void remove();
    btTransform parseToBulletTransform(Vector3 pos, Vector3 rot);
    std::vector<Vector3> getVertexFromMesh(std::string meshName);
    const btVector3 parseToBulletVector(const Vector3& v) const;
    const Vector3 parseFromBulletVector(const btVector3& v) const;
    btCollisionShape* createShapeWithVertices(Vector3 _dim, std::string bodyMeshName, bool isConvex);
    btCollisionShape* createBodyShape(RigidBody::RigidBodyType rbType, Vector3 _dim, std::string bodyMeshName, bool isConvex);
    void clear();


};

PhysicsSystem* Physics()
{
    return PhysicsSystem::getInstance();
}