#include "RigidBody.h"
#include "PhysicsMain.h"
#include "Vector3.h"
#include "Vector4.h"
#include <btBulletDynamicsCommon.h>
#include "../checkML.h"

RigidBody::RigidBody(std::string bodyMeshName, Vector3 pos, Vector3 scale, float m, bool useG, bool isK) :
mass(m), useGravity(useG), isKinematic(isK) {
	freezePosition = std::vector<bool>(3, false);
	freezeRotation = std::vector<bool>(3, false);
	createRigidBodyComponent(RigidBodyType::Box, pos, scale, bodyMeshName);
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

bool RigidBody::getKinematic() { return isKinematic; }
bool RigidBody::getUseGravity() { return useGravity; }


void RigidBody::setKinematic(bool sK) { isKinematic = sK; }

void RigidBody::setUsingGravity(bool uG) {
	if (uG) rigidBody->applyGravity();
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

void RigidBody::createRigidBodyComponent(RigidBodyType rbType, Vector3 pos, Vector3 scale, std::string bodyMeshName, bool isConvex)
{
	rigidBody = PhysicsSystem::getInstance()->createRigidBody(rbType, mass, scale, pos, bodyMeshName, isConvex, isKinematic);
}

void RigidBody::addForce(Vector3 vec) {
	btVector3 forc = btVector3(vec.GetX(), vec.GetY(), vec.GetZ());
	rigidBody->applyForce(forc, btVector3());
}

void RigidBody::addTorque(Vector3 vec)
{
	btVector3 torque = btVector3(vec.GetX(), vec.GetY(), vec.GetZ());
	rigidBody->applyTorque(torque);
}

Vector3 RigidBody::getRbPosition()
{
	btTransform t;
	rigidBody->getMotionState()->getWorldTransform(t);
	return Physics()->parseFromBulletVector(t.getOrigin());
}

void RigidBody::setRbPosition(Vector3 vec)
{
	rigidBody->getMotionState()->setWorldTransform(Physics()->parseToBulletTransform(vec, getRotation()));
}

void RigidBody::setRbRotation(Vector4 vec)
{
	rigidBody->getMotionState()->setWorldTransform(Physics()->parseToBulletTransform(getRbPosition(), vec));
}

Vector4 RigidBody::getRotation()
{
	btTransform t;
	rigidBody->getMotionState()->getWorldTransform(t);
	auto quat = t.getRotation();
	return Vector4(quat.getX(), quat.getY(), quat.getZ(), quat.getW());
}

