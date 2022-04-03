#include "RigidBody.h"
#include "PhysicsMain.h"
#include "Transform.h"
#include "Entity.h"
#include "ComponentManager.h"
#include "AegisComponent.h"
#include "Vector3.h"
#include <btBulletDynamicsCommon.h>

RigidBody::RigidBody(Entity* ent, std::string bodyMeshName, float m, bool useG, bool isK) : AegisComponent(),
mass(m), useGravity(useG), isKinematic(isK) {
	setEntity(ent);
	freezePosition = std::vector<bool>(3, false);
	freezeRotation = std::vector<bool>(3, false);
	transform = ent->getComponent<Transform>();
	createRigidBodyComponent(RigidBodyType::Box);

	ComponentManager::getInstance()->RegisterComponent<RigidBody>("RigidBody");
}

void RigidBody::init() {
	/*btDefaultMotionState* ms = new btDefaultMotionState();
	btBoxShape* shape = new btBoxShape(btVector3(10, 10, 10)); //COMPROBAR FUNCIONALIDAD
	rigidBody = new btRigidBody(mass, ms, shape);
	rigidBody->setGravity(btVector3(0, -10, 0)); //DEFAULT???
	*/
	createRigidBodyComponent(RigidBodyType::Box);
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

void RigidBody::createRigidBodyComponent(RigidBodyType rbType, std::string bodyMeshName, bool isConvex)
{
	Vector3 scale = transform->GetScale();
	Vector3 pos = transform->GetPosition();
	rigidBody = PhysicsSystem::getInstance()->createRigidBody(rbType, mass, transform->GetScale(), transform->GetPosition(), bodyMeshName, isConvex);
}

void RigidBody::addForce(Vector3 vec) {
	btVector3 forc = btVector3(vec.GetX(), vec.GetY(), vec.GetZ());
	rigidBody->applyForce(forc, btVector3());
}

void RigidBody::fixedUpdate() {
	if (isKinematic) return;
}


