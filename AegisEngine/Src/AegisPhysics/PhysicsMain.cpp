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
#include "PhysicsMain.h"
#include "btBulletDynamicsCommon.h"
#include "Entity.h"
#include "RigidbodyComponent.h"
#include "DebugDrawer.h"
#include "OgreWrapper.h"
#include "OgreSceneManager.h"

PhysicsSystem::PhysicsSystem() {
}

/// This is a Hello World program for running a basic Bullet physics simulation
void PhysicsSystem::Init(Ogre::SceneManager* mScene)
{
	scene = mScene;
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
	 
	//Create lambda func for gContactAddedCallback
	gContactAddedCallback = [](btManifoldPoint& cp, const btCollisionObjectWrapper* colObj0Wrap, int partId0, int index0, const btCollisionObjectWrapper* colObj1Wrap, int partId1, int index1)
	{
		std::cout << "Col\n";
		return true;
	};;
	//fileLoader = new btBulletWorldImporter(dynamicsWorld);


	mDebugDrawer = new OgreDebugDrawer(scene);
	mDebugDrawer->setDebugMode(btIDebugDraw::DBG_DrawWireframe);
	dynamicsWorld->setDebugDrawer(mDebugDrawer);
}

PhysicsSystem::~PhysicsSystem() {
	remove(); 
}


void PhysicsSystem::remove() {
	clear();

	//delete dynamics world
	delete dynamicsWorld; //SALTA ERROR DE EJECUCION---------------------
	//delete solver
	delete solver;
	//delete broadphase
	delete overlappingPairCache;
	//delete dispatcher
	delete dispatcher;
	delete collisionConfiguration;
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
			delete body->getCollisionShape();
		}
		dynamicsWorld->removeCollisionObject(obj);
		delete obj;
	}
}

/// Do some simulation
void PhysicsSystem::update(float deltaTime, float timeStep, int maxSteps) {
	///-----stepsimulation_start-----
	dynamicsWorld->stepSimulation(deltaTime, maxSteps, timeStep);
	dynamicsWorld->debugDrawWorld();
	auto a = dynamicsWorld->getDebugDrawer();
	//btIDebugDraw::drawBox(btVector3(0, 0, 0), btVector3(20, 20, 20), btVector3(1, 0, 0));
	dynamicsWorld->clearForces();
#if defined _DEBUG
	dynamicsWorld->debugDrawWorld();
#endif
	
}

void PhysicsSystem::checkCollision()
{
	std::map<std::pair<RigidBody*, RigidBody*>, bool> newContacts;

	int numManifolds = dynamicsWorld->getDispatcher()->getNumManifolds();
	for (int i = 0; i < numManifolds; i++)
	{
		btPersistentManifold* contactManifold = dynamicsWorld->getDispatcher()->getManifoldByIndexInternal(i);
		const btCollisionObject* obA = contactManifold->getBody0();
		const btCollisionObject* obB = contactManifold->getBody1();

		int numContacts = contactManifold->getNumContacts();
		for (int j = 0; j < numContacts; j++)
		{
			btManifoldPoint& pt = contactManifold->getContactPoint(j);
			if (pt.getDistance() < 0.f)
			{
				RigidBody* rigidBodyA = (RigidBody*)obA->getUserPointer(), * rigibBodyB = (RigidBody*)obB->getUserPointer();

				if (rigidBodyA != nullptr || rigibBodyB != nullptr && (rigidBodyA->isActive() && rigibBodyB->isActive()) )
				{
					if (rigidBodyA > rigibBodyB) std::swap(rigidBodyA, rigibBodyB);
					std::pair<RigidBody*, RigidBody*> col = { rigidBodyA, rigibBodyB };
					newContacts[col] = true;
					
					
					//Llamamos al collisionEnter si no estaban registrados.
					if (contacts.find(col) == contacts.end()) {
						//std::cout << "a";
						CollisionEnterCallbacks(col);
					}
					else {
						//CollisionStayCallbacks(col);
					}
				}
				
				break;
			}
		}
	}


	for (auto it = contacts.begin(); it != contacts.end(); it++) 	{
		std::pair<RigidBody*, RigidBody*> col = (*it).first;
		if (newContacts.find(col) == newContacts.end());
			//CollisionExitCallbacks(col);
	}

	contacts = newContacts;
}

void PhysicsSystem::CollisionEnterCallbacks(std::pair<RigidBody*, RigidBody*>& col) {
	Entity* goA = col.first->rbC->mEntity_, * goB = col.second->rbC->mEntity_;
	bool aTrigger = col.first->isTrigger() , bTrigger = col.second->isTrigger();
	
	 if (aTrigger || bTrigger) {
		 if (aTrigger && bTrigger) {
			 goA->onTrigger(goB);
			 goB->onTrigger(goA);
		 }
		 else if (aTrigger && !bTrigger) {
			 goA->onTrigger(goB);
			 goB->onCollision(goA);
		 }
		 else if (!aTrigger && bTrigger) {
			 goA->onCollision(goB);
			 goB->onTrigger(goA);
		 }
	 }
	 else {
		 goA->onCollision(goB);
		 goB->onCollision(goA);
	 }
}

void PhysicsSystem::CollisionExitCallbacks(std::pair<RigidBody*, RigidBody*>& col)
{
}


void PhysicsSystem::removeRigidbody(btCollisionObject* rb) {
	//remove the rigidbodies from the dynamics world and delete them

	btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[rb->getWorldArrayIndex()];
	btRigidBody* body = btRigidBody::upcast(obj);
	if (body && body->getMotionState())
	{
		delete body->getMotionState();
	}
	dynamicsWorld->removeCollisionObject(obj);
	delete obj;
}

btTransform PhysicsSystem::parseToBulletTransform(Vector3 pos, Vector3 rot) {
	btTransform t;
	t.setIdentity();
	t.setOrigin({ btScalar(pos.GetX()), btScalar(pos.GetY()), btScalar(pos.GetZ()) });
	btQuaternion quat = (btQuaternion(btScalar(rot.GetZ()) * SIMD_RADS_PER_DEG, btScalar(rot.GetY()) * SIMD_RADS_PER_DEG, btScalar(rot.GetX()) * SIMD_RADS_PER_DEG)); quat.normalize();
	t.setRotation(quat);
	return t;
}

btTransform PhysicsSystem::parseToBulletTransform(Vector3 pos, Vector4 rot) {
	btTransform t;
	t.setIdentity();
	t.setOrigin({ btScalar(pos.GetX()), btScalar(pos.GetY()), btScalar(pos.GetZ()) });
	btQuaternion quat = btQuaternion(rot.x, rot.y, rot.z, rot.w);
	quat.normalize();
	t.setRotation(quat);
	return t;
}

const btVector3 PhysicsSystem::parseToBulletVector(const Vector3& v) const
{
	return btVector3(btScalar(v.GetX()), btScalar(v.GetY()), btScalar(v.GetZ()));
}

const Vector3 PhysicsSystem::parseFromBulletVector(const btVector3& v) const
{
	return Vector3(double(v.x()), double(v.y()), double(v.z()));
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
		//char fileName[100];
		//strcpy(fileName, bodyMeshName.c_str());
		//fileLoader->loadFile(fileName);
		//rbShape = createShapeWithVertices(_dim, bodyMeshName, isConvex);
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

btRigidBody* PhysicsSystem::createRigidBody(RigidBody::RigidBodyType rbType, float _mass, Vector3 _dim, Vector3 _pos, Vector4 rotation, std::string bodyMeshName, bool isConvex, bool isKinematic, bool useGravity) {
	btCollisionShape* rbShape = createBodyShape(rbType, _dim, bodyMeshName, isConvex);
	rbShape->setMargin(0.0f);

	btTransform groundTransform;
	groundTransform.setIdentity();
	groundTransform.setOrigin(btVector3(_pos.GetX(), _pos.GetY(), _pos.GetZ()));
	btQuaternion quat = btQuaternion(rotation.x, rotation.y, rotation.z, rotation.w);
	groundTransform.setRotation(quat);
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
	
	if (isKinematic)
		body->setCollisionFlags(btCollisionObject::CF_KINEMATIC_OBJECT);
	else
	{
		body->setCollisionFlags(btCollisionObject::CF_DYNAMIC_OBJECT);
		body->setActivationState(DISABLE_DEACTIVATION); //Never sleep
	}
	
	//add the body to the dynamics world
	dynamicsWorld->addRigidBody(body);
	if(!useGravity)
		body->setGravity({ 0,0,0 });

	return body;
}


