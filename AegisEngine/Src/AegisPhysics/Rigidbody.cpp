#include "RigidBody.h"
#include "PhysicsMain.h"
#include "Vector4.h"
#include <btBulletDynamicsCommon.h>
#include <btBulletCollisionCommon.h>
//#include "../checkML.h"

RigidBody::RigidBody(std::string bodyMeshName, Vector3 pos, Vector3 scale, RigidbodyComponent* r, float m, bool useG, bool isK) :
	mass(m), useGravity(useG), isKinematic(isK) {
	freezePosition = std::vector<bool>(3, false);
	freezeRotation = std::vector<bool>(3, false);
	createRigidBodyComponent(RigidBodyType::Box, pos, scale, bodyMeshName); rbC = r;
	//if (t)rigidBody->setCollisionFlags(rigidBody->getCollisionFlags() | btCollisionObject::CF_NO_CONTACT_RESPONSE);
}

void RigidBody::init() {
	/*btDefaultMotionState* ms = new btDefaultMotionState();
	btBoxShape* shape = new btBoxShape(btVector3(10, 10, 10)); //COMPROBAR FUNCIONALIDAD
	rigidBody = new btRigidBody(mass, ms, shape);
	rigidBody->setGravity(btVector3(0, -10, 0)); //DEFAULT???
	*/
	//createRigidBodyComponent(RigidBodyType::Box);
}

RigidBody::~RigidBody()
{
	delete rigidBody->getCollisionShape();
	Physics()->removeRigidbody(this->rigidBody);
}

void RigidBody::createRigidBodyComponent(RigidBodyType rbType, Vector3 pos, Vector3 scale, std::string bodyMeshName, bool isConvex)
{
	rigidBody = PhysicsSystem::getInstance()->createRigidBody(rbType, mass, scale, pos, bodyMeshName, isConvex, isKinematic, useGravity);
	
	rigidBody->setUserPointer(this);
}


//GETS--------------------------------------------------------------------------------------------------
bool RigidBody::getKinematic() { return isKinematic; }
bool RigidBody::getUseGravity() { return useGravity; }

Vector3 RigidBody::getTotalForce() {
	btVector3 forc = rigidBody->getTotalForce();
	return Vector3(forc.x(), forc.y(), forc.z());
};

Vector3 RigidBody::getRbPosition()
{
	btTransform t;
	rigidBody->getMotionState()->getWorldTransform(t);
	return Physics()->parseFromBulletVector(t.getOrigin());
}

Vector4 RigidBody::getRotation()
{
	btTransform t;
	rigidBody->getMotionState()->getWorldTransform(t);
	auto quat = t.getRotation();
	return Vector4(quat.getX(), quat.getY(), quat.getZ(), quat.getW());
}

bool RigidBody::isActive() const
{
	return rigidBody->isActive();
}

bool RigidBody::isTrigger()
{
	return trigger;
}

//SETS------------------------------------------------------------------------------------------------------
void RigidBody::setActive(bool active)
{
	rigidBody->activate(true); // Equivalent to rigidbody->setActivationState(ACTIVE_TAG)
	//std::cout << "Activation state " << rigidBody->getActivationState() << std::endl;

	// What every activation state means
	// ACTIVE_TAG 1
	// ISLAND_SLEEPING 2
	// WANTS_DEACTIVATION 3
	// DISABLE_DEACTIVATION 4
	// DISABLE_SIMULATION 5
}

void RigidBody::setKinematic(bool sK) { isKinematic = sK; }

void RigidBody::setUsingGravity(bool uG) {

	if (uG)rigidBody->setGravity({ 0, -9.8, 0 });
	else rigidBody->clearGravity();
}

void RigidBody::setGravity(Vector3 vec) {
	btVector3 grav = btVector3(vec.GetX(), vec.GetY(), vec.GetZ());
	rigidBody->setGravity(grav);
}

void RigidBody::setFreezeRotation(bool _x, bool _y, bool _z)
{
	freezeRotation[0] = _x;
	freezeRotation[1] = _y;
	freezeRotation[2] = _z;
}

bool RigidBody::RaycastWorld(Vector3 f) {
	btTransform aux; btVector3 forward = Physics()->parseToBulletVector(f);
	btVector3 posAct; rigidBody->getMotionState()->getWorldTransform(aux); posAct = aux.getOrigin();
		btCollisionWorld::ClosestRayResultCallback RayCallback(posAct, posAct + forward*10);
		
		// Perform raycast
		Physics()->dynamicsWorld->rayTest(posAct, posAct + forward * 10, RayCallback);
		if (RayCallback.hasHit()) {

			return true;
		}
	
		return false;
	//return false;
}

void RigidBody::setRbPosition(Vector3 vec)
{
	btTransform t = Physics()->parseToBulletTransform(vec, getRotation());
	rigidBody->setWorldTransform(t);
	rigidBody->getMotionState()->setWorldTransform(t);
	rigidBody->setLinearVelocity({ 0, 0, 0 });
	rigidBody->setAngularVelocity({ 0, 0, 0 });
	rigidBody->clearForces();
}

void RigidBody::setRbRotation(Vector4 vec)
{
	rigidBody->getMotionState()->setWorldTransform(Physics()->parseToBulletTransform(getRbPosition(), vec));
}

//FORCES---------------------------------------------------------------------------------------------------------
void RigidBody::addForce(Vector3 vec) {
	btVector3 forc = btVector3(vec.GetX(), vec.GetY(), vec.GetZ());
	rigidBody->applyForce(forc, btVector3());
}


Vector3 RigidBody::AccelerateTo(Vector3 targetVelocity, float deltaTime, float maxAcceleration)
{
	Vector3 deltaVelocity = targetVelocity - Physics()->parseFromBulletVector(rigidBody->getLinearVelocity());
	Vector3 acceleration = deltaVelocity / deltaTime;

	if (acceleration.magnitudeSquared() > maxAcceleration * maxAcceleration)
		acceleration = acceleration.getNormalized() * maxAcceleration;

	acceleration *= rigidBody->getMass();
	addForce(acceleration);
	return acceleration;
}

void RigidBody::addTorque(Vector3 vec)
{
	btVector3 torque = btVector3(vec.GetX(), vec.GetY(), vec.GetZ());
	rigidBody->applyTorque(torque);
}

void RigidBody::clearForces()
{
	rigidBody->clearForces();
}

void RigidBody::changeGravity(Vector3 acc)
{
	rigidBody->setGravity(Physics()->parseToBulletVector(acc));
}



