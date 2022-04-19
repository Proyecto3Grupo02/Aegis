/*
Bullet Continuous Collision Detection and Physics Library
Copyright (c) 2003-2007 Erwin Coumans  https://bulletphysics.org

This software is provided 'as-is', without any express or implied warranty.
In no event will the authors be held liable for any damages arising from the use of this software.
Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it freely,
subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.
*/

///-----includes_start-----
#include "btBulletDynamicsCommon.h"
#include <stdio.h>
#include "PhysicsMain.h"
#include "Vector3.h"
/// This is a Hello World program for running a basic Bullet physics simulation



void PhysicsSystem::Init()
{

	///collision configuration contains default setup for memory, collision setup. Advanced users can create their own configuration.
	collisionConfiguration = new btDefaultCollisionConfiguration();

	///use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
	dispatcher = new btCollisionDispatcher(collisionConfiguration);

	///btDbvtBroadphase is a good general purpose broadphase. You can also try out btAxis3Sweep.
	overlappingPairCache = new btDbvtBroadphase();

	///the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
	solver = new btSequentialImpulseConstraintSolver;

	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration);

	dynamicsWorld->setGravity(btVector3(0, -10, 0));


}
///create a few basic rigid bodies

////the ground is a cube of side 100 at position y = -56.
////the sphere will hit it at y = -6, with center at -5
//{
//	btCollisionShape* groundShape = new btBoxShape(btVector3(btScalar(50.), btScalar(50.), btScalar(50.)));

//	collisionShapes.push_back(groundShape);

//	btTransform groundTransform;
//	groundTransform.setIdentity();
//	groundTransform.setOrigin(btVector3(0, -56, 0));

//	btScalar mass(0.);

//	//rigidbody is dynamic if and only if mass is non zero, otherwise static
//	bool isDynamic = (mass != 0.f);

//	btVector3 localInertia(0, 0, 0);
//	if (isDynamic)
//		groundShape->calculateLocalInertia(mass, localInertia);

//	//using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
//	btDefaultMotionState* myMotionState = new btDefaultMotionState(groundTransform);
//	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, groundShape, localInertia);
//	btRigidBody* body = new btRigidBody(rbInfo);

//	//add the body to the dynamics world
//	dynamicsWorld->addRigidBody(body);
//}

//{
//	//create a dynamic rigidbody

//	//btCollisionShape* colShape = new btBoxShape(btVector3(1,1,1));
//	btCollisionShape* colShape = new btSphereShape(btScalar(1.));
//	collisionShapes.push_back(colShape);

//	/// Create Dynamic Objects
//	btTransform startTransform;
//	startTransform.setIdentity();

//	btScalar mass(1.f);

//	//rigidbody is dynamic if and only if mass is non zero, otherwise static
//	bool isDynamic = (mass != 0.f);

//	btVector3 localInertia(0, 0, 0);
//	if (isDynamic)
//		colShape->calculateLocalInertia(mass, localInertia);

//	startTransform.setOrigin(btVector3(2, 10, 0));

//	//using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
//	btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
//	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, colShape, localInertia);
//	btRigidBody* body = new btRigidBody(rbInfo);

//	dynamicsWorld->addRigidBody(body);
//}

/// Do some simulation
void PhysicsSystem::update() {
	///-----stepsimulation_start-----
	float timeStep = 1.f / 50.f;
	dynamicsWorld->stepSimulation(timeStep, 10);
	
	std::cout << "Colisions: " << dynamicsWorld->getNumCollisionObjects() << " ";
	for (int j = dynamicsWorld->getNumCollisionObjects() - 1; j >= 0; j--)
	{
		btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[j];
		btRigidBody* body = btRigidBody::upcast(obj);
		btTransform trans;
		if (body && body->getMotionState())
		{
			body->getMotionState()->getWorldTransform(trans);
		}
		else
		{
			trans = obj->getWorldTransform();
		}
		printf("world pos object %d = %f,%f,%f\n", j, float(trans.getOrigin().getX()), float(trans.getOrigin().getY()), float(trans.getOrigin().getZ()));
	}
}

///-----stepsimulation_end-----

//cleanup in the reverse order of creation/initialization

///-----cleanup_start-----
void PhysicsSystem::clear() {
	//remove the rigidbodies from the dynamics world and delete them
	for (int i = dynamicsWorld->getNumCollisionObjects() - 1; i >= 0; i--)
	{
		btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[i];
		btRigidBody* body = btRigidBody::upcast(obj);
		if (body && body->getMotionState())
		{
			delete body->getMotionState();
		}
		dynamicsWorld->removeCollisionObject(obj);
		delete obj;
	}

	//delete collision shapes
	for (int j = 0; j < collisionShapes.size(); j++)
	{
		btCollisionShape* shape = collisionShapes[j];
		collisionShapes[j] = 0;
		delete shape;
	}


}

void PhysicsSystem::remove() {
	//delete dynamics world
	delete dynamicsWorld;

	//delete solver
	delete solver;

	//delete broadphase
	delete overlappingPairCache;

	//delete dispatcher
	delete dispatcher;

	delete collisionConfiguration;

	//next line is optional: it will be cleared by the destructor when the array goes out of scope
	collisionShapes.clear();


}

btTransform PhysicsSystem::parseToBulletTransform(Vector3 pos, Vector3 rot)
{
	btTransform t;
	t.setIdentity();
	t.setOrigin({ btScalar(pos.GetX()), btScalar(pos.GetY()), btScalar(pos.GetZ()) });
	btQuaternion quat = (btQuaternion(btScalar(rot.GetZ()) * SIMD_RADS_PER_DEG, btScalar(rot.GetY()) * SIMD_RADS_PER_DEG, btScalar(rot.GetX()) * SIMD_RADS_PER_DEG)); quat.normalize();
	t.setRotation(quat);
	return t;
}
std::vector<Vector3> PhysicsSystem::getVertexFromMesh(std::string meshName)
{
	std::vector<Vector3> vertex;

	return vertex;
}

const btVector3 PhysicsSystem::parseToBulletVector(const Vector3& v) const
{
	return btVector3(btScalar(v.GetX()), btScalar(v.GetY()), btScalar(v.GetZ()));
}

const Vector3 PhysicsSystem::parseFromBulletVector(const btVector3& v) const
{
	return Vector3(double(v.x()), double(v.y()), double(v.z()));
}

btCollisionShape* PhysicsSystem::createShapeWithVertices(Vector3 _dim, std::string bodyMeshName, bool isConvex)
{
	btCollisionShape* rbShape;
	std::vector<Vector3> vertex = getVertexFromMesh(bodyMeshName);

	if (isConvex) {
		rbShape = new btConvexHullShape();
		for (int i = 0; i < vertex.size(); ++i) {
			Vector3 v = vertex[i];
			btVector3 btv = btVector3(v.GetX(), v.GetY(), v.GetZ());
			((btConvexHullShape*)rbShape)->addPoint(btv);
		}
	}

	else {
		btTriangleMesh* mesh = new btTriangleMesh();
		for (int i = 0; i < vertex.size(); i += 3)
		{
			Vector3 v1 = vertex[i];
			Vector3 v2 = vertex[i + 1];
			Vector3 v3 = vertex[i + 2];

			btVector3 bv1 = parseToBulletVector(v1);
			btVector3 bv2 = parseToBulletVector(v2);
			btVector3 bv3 = parseToBulletVector(v3);

			mesh->addTriangle(bv1, bv2, bv3);
		}
		rbShape = new btBvhTriangleMeshShape(mesh, true);
	}
	return rbShape;
}

btCollisionShape* PhysicsSystem::createBodyShape(RigidBody::RigidBodyType rbType, Vector3 _dim, std::string bodyMeshName, bool isConvex)
{
	btCollisionShape* rbShape = nullptr;
	switch (rbType) {
	case RigidBody::RigidBodyType::Box:
		rbShape = new btBoxShape(btVector3(btScalar(_dim.GetX() / 2.0f), btScalar(_dim.GetY() / 2.0f), btScalar(_dim.GetZ() / 2.0f)));
		break;
	case RigidBody::RigidBodyType::Sphere:
		rbShape = new btSphereShape(btScalar(_dim.GetX() / 2.0f));
		break;
	case RigidBody::RigidBodyType::Custom:
		rbShape = createShapeWithVertices(_dim, bodyMeshName, isConvex);
		break;
	case RigidBody::RigidBodyType::CapsuleX:
		rbShape = new btCapsuleShapeX(btScalar(_dim.GetZ() / 2.0f), btScalar(_dim.GetX()));
		break;
	case RigidBody::RigidBodyType::CapsuleZ:
		rbShape = new btCapsuleShapeZ(btScalar(_dim.GetX() / 2.0f), btScalar(_dim.GetZ()));
		break;
	default: break;
	}

	return rbShape;
}

btRigidBody* PhysicsSystem::createRigidBody(RigidBody::RigidBodyType rbType, float _mass, Vector3 _dim, Vector3 _pos, std::string bodyMeshName, bool isConvex, bool isKinematic) {
	btCollisionShape* rbShape = createBodyShape(rbType, _dim, bodyMeshName, isConvex);


	//= 
	collisionShapes.push_back(rbShape);

	btTransform groundTransform;
	groundTransform.setIdentity();
	groundTransform.setOrigin(btVector3(_pos.GetX(), _pos.GetY(), _pos.GetZ()));
	btScalar mass(_mass);

	btVector3 localInertia(0, 0, 0);

	//rigidbody is dynamic if and only if mass is non zero, otherwise static
	if (!isKinematic)
		rbShape->calculateLocalInertia(mass, localInertia);
	else
		mass = 0;

	//using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
	btDefaultMotionState* myMotionState = new btDefaultMotionState(groundTransform);
	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, rbShape, localInertia);
	btRigidBody* body = new btRigidBody(rbInfo);

	//add the body to the dynamics world
	dynamicsWorld->addRigidBody(body);

	return body;
}


PhysicsSystem::PhysicsSystem()
{
}

PhysicsSystem::~PhysicsSystem()
{
}
