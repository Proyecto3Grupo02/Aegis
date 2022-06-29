#include "RigidBody.h"
#include "PhysicsMain.h"
#include "Vector4.h"
#include "RigidbodyComponent.h"
#include "Entity.h"
#include <btBulletDynamicsCommon.h>

RigidBody::RigidBody(std::string bodyMeshName, Vector3 pos, Vector3 scale, Vector4 rotation, RigidbodyComponent* r, float m, bool useG, bool isK, bool isT, float damp) :
	mass(m), useGravity(useG), isKinematic(isK), damping(damp) {
	
	freezeRotation = std::vector<bool>(3, false);
	rbC = r;
	trigger = isT;
	createRigidBodyComponent(RigidBodyType::Box, pos, scale, rotation, bodyMeshName, isT, damping);
	if (trigger)
		rigidBody->setCollisionFlags(rigidBody->getCollisionFlags() | btCollisionObject::CF_NO_CONTACT_RESPONSE);
	
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
	PhysicsSys->removeRigidbody(this->rigidBody);
	rigidBody = nullptr;
}

void RigidBody::createRigidBodyComponent(RigidBodyType rbType, Vector3 pos, Vector3 scale, Vector4 rotation, std::string bodyMeshName, bool isConvex, float damp)
{
	rigidBody = PhysicsSystem::getInstance()->createRigidBody(rbType, mass, scale, pos, rotation, bodyMeshName, isConvex, isKinematic, useGravity, damp);
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
	return PhysicsSys->parseFromBulletVector(t.getOrigin());
}

Vector4 RigidBody::getRotation()
{
	btTransform t;
	rigidBody->getMotionState()->getWorldTransform(t);
	auto quat = t.getRotation();
	return Vector4(quat.getX(), quat.getY(), quat.getZ(), quat.getW());
}
float RigidBody::getMass()
{
	return rigidBody->getMass();
}
bool RigidBody::isActive() const
{
	return rigidBody->isActive();
}

bool RigidBody::isTrigger()
{
	return trigger;
}

void RigidBody::setTrigger(bool trig)
{	
	if (trig)
	{
		rigidBody->setCollisionFlags(rigidBody->getCollisionFlags() | btCollisionObject::CF_NO_CONTACT_RESPONSE);
		trigger = true;
	}
	else {
		rigidBody->setCollisionFlags(rigidBody->getCollisionFlags() | btCollisionObject::CF_DYNAMIC_OBJECT);
		trigger = false;
	}
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
	useGravity = uG;
	if (uG)rigidBody->setGravity({ 0, -9.8, 0 });
	else rigidBody->setGravity({ 0,0,0 });
}

void RigidBody::setGravity(Vector3 vec) {
	btVector3 grav = btVector3(vec.getX(), vec.getY(), vec.getZ());
	rigidBody->setGravity(grav);
}

void RigidBody::setFreezeRotation(bool _x, bool _y, bool _z) {
	freezeRotation[0] = _x;
	freezeRotation[1] = _y;
	freezeRotation[2] = _z;

	rigidBody->setLinearFactor(btVector3(_x, _y, _z));
	rigidBody->setAngularFactor(btVector3(!_x, !_y, !_z));

}

void RigidBody::setDamping(float damp)
{
	damping = damp;
	rigidBody->setDamping(damp, damp);
}

float RigidBody::getDamping()
{
	return damping;
}

Entity* RigidBody::rayCast(Vector3 origin, Vector3& dest) {
	btVector3 _origin = PhysicsSys->parseToBulletVector(origin);
	btVector3 _dest = PhysicsSys->parseToBulletVector(dest);
	btCollisionWorld::ClosestRayResultCallback RayCallback(_origin, _dest);

	// Perform raycast
	PhysicsSys->dynamicsWorld->rayTest(_origin, _dest, RayCallback);
	if (RayCallback.hasHit()) {		
		RigidBody* rb = (RigidBody*)RayCallback.m_collisionObject->getUserPointer();
		return rb->getRbComponent()->getEntity();
	}

	return nullptr;
	
}

void RigidBody::setRbPosition(Vector3 vec)
{
	btTransform t = PhysicsSys->parseToBulletTransform(vec, getRotation());
	rigidBody->setWorldTransform(t);
	rigidBody->getMotionState()->setWorldTransform(t);
	//rigidBody->setLinearVelocity({ 0, 0, 0 });
	//rigidBody->setAngularVelocity({ 0, 0, 0 });
	//rigidBody->clearForces();
}

void RigidBody::setRbRotation(Vector4 vec)
{
	btTransform t = PhysicsSys->parseToBulletTransform(getRbPosition(), vec);
	rigidBody->setWorldTransform(t);
	//rigidBody->setLinearVelocity({ 0, 0, 0 });
	//rigidBody->setAngularVelocity({ 0, 0, 0 });
	//rigidBody->clearForces();
}

//FORCES---------------------------------------------------------------------------------------------------------
void RigidBody::addForce(Vector3 vec) {
	btVector3 forc = btVector3(vec.getX(), vec.getY(), vec.getZ());
	rigidBody->applyForce(forc, btVector3());
}


Vector3 RigidBody::accelerateTo(Vector3 targetVelocity, float deltaTime, float maxAcceleration)
{
	Vector3 deltaVelocity = targetVelocity - PhysicsSys->parseFromBulletVector(rigidBody->getLinearVelocity());
	Vector3 acceleration = deltaVelocity / deltaTime;

	if (acceleration.magnitudeSquared() > maxAcceleration * maxAcceleration)
		acceleration = acceleration.getNormalized() * maxAcceleration;

	acceleration *= rigidBody->getMass();
	addForce(acceleration);
	return acceleration;
}

void RigidBody::addTorque(Vector3 vec)
{
	btVector3 torque = btVector3(vec.getX(), vec.getY(), vec.getZ());
	rigidBody->applyTorque(torque);
}

void RigidBody::clearForces()
{
	rigidBody->setLinearVelocity({ 0, 0, 0 });
	rigidBody->setAngularVelocity({ 0, 0, 0 });
	rigidBody->clearForces();
}

void RigidBody::changeGravity(Vector3 acc)
{
	rigidBody->setGravity(PhysicsSys->parseToBulletVector(acc));
}

void RigidBody::setAngularFactor() {
	rigidBody->setAngularFactor(btVector3(0, 0, 0));
}

void RigidBody::enableCol()
{
	//rigidBody->setCollisionFlags(rigidBody->getCollisionFlags() ^ btCollisionObject::CF_NO_CONTACT_RESPONSE);
	rigidBody->setCollisionFlags(rigidBody->getCollisionFlags() & (~btCollisionObject::CF_NO_CONTACT_RESPONSE));
}
RigidbodyComponent* RigidBody::getRbComponent()
{
	return rbC;
}
void RigidBody::disableCol()
{
	rigidBody->setCollisionFlags(rigidBody->getCollisionFlags() | btCollisionObject::CF_NO_CONTACT_RESPONSE);
}

void RigidBody::setLinearVelocity() {
	btVector3 velocity = rigidBody->getAngularVelocity();
	rigidBody->setAngularFactor({ velocity.getX(), 0, velocity.getZ() });
}

void RigidBody::resetVelocity()
{
	rigidBody->setLinearVelocity({0.0, 0.0, 0.0});
}
