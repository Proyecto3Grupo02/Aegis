#include "RigidbodyComponent.h"

#include "Entity.h"
#include <Scene.h>
#include "../Utils/GameLoopData.h"

RigidbodyComponent::RigidbodyComponent(Entity* ent, std::string bodyMeshName, float m, bool useG, bool isK, bool ray)
	: AegisComponent("Rigidbody", ent)
{
	transform = ent->GetTransform();
	initialPos = transform->GetPosition();
	rigidbody = new RigidBody(bodyMeshName, transform->GetPosition(), transform->GetScale(),this, m, useG, isK, ray);
	mEntity_->getScene()->AddPhysicsEntity(this);

	SetDataAsInnerType(this);
}

RigidbodyComponent::~RigidbodyComponent()
{
	delete rigidbody;
	mEntity_->getScene()->RemovePhysicsEntity(this->physicsEntityIt);
};

void RigidbodyComponent::lateUpdate(float deltaTime) {}

void RigidbodyComponent::fixedUpdate() {	
	if (rigidbody->RaycastWorld(transform->GetForward())) {
		std::cout << "a";
		int random; random = rand() % 3; while (random == 1) random = rand() % 3; random--; random *= 20;
		rigidbody->addTorque({ 0,float(random),0 });
	}
}

void RigidbodyComponent::SyncToTransform()
{
	Vector3 updatedPos = rigidbody->getRbPosition();
	transform->SetPosition(updatedPos);
	auto quat = rigidbody->getRotation();
	Ogre::Quaternion ogreQuat(quat.w, quat.x, quat.y, quat.z);
	transform->SetRotation(ogreQuat);
}

void RigidbodyComponent::SetIterator(std::list<RigidbodyComponent*>::iterator physicsEntityIt)
{
	this->physicsEntityIt = physicsEntityIt;
}

bool RigidbodyComponent::isActive() const
{
	return rigidbody->isActive();
}

void RigidbodyComponent::AddForce(Vector3 force) {
	rigidbody->addForce(force);
}

Vector3 RigidbodyComponent::AccelerateTo(Vector3 targetVelocity, float maxAcceleration)
{
	return rigidbody->AccelerateTo(targetVelocity, Time()->deltaTime, maxAcceleration);
}

void RigidbodyComponent::AddForceForward(float force) {
	Vector3 rot = transform->GetForward();
	AddForce(rot * force);
}

void RigidbodyComponent::AddTorque(Vector3 torque) {
	rigidbody->addTorque(torque);
}

Vector3 RigidbodyComponent::GetForce() const {
	return rigidbody->getTotalForce();
}

Vector3 RigidbodyComponent::GetPosition() const {
	return rigidbody->getRbPosition();
}

void RigidbodyComponent::SetPosition(Vector3 pos) {
	rigidbody->setRbPosition(pos);
}

//LUA-------------------------------------------------------------------------------------------------------
RigidbodyComponent* CreateRigidbody(Entity* ent, LuaRef args) //Doesn't belong to this class
{
	std::string bodyName = ent->getName();
	float mass = LuaMngr()->ParseFloat(args["mass"], 1);
	bool useGravity = LuaMngr()->ParseBool(args["useGravity"], true);
	bool isKinematic = LuaMngr()->ParseBool(args["isKinematic"], false);
	bool needRaycast = LuaMngr()->ParseBool(args["needRaycast"], false);
	return new RigidbodyComponent(ent, bodyName, mass, useGravity, isKinematic);
}

void RigidbodyComponent::ConvertToLua(lua_State* state)
{
	getGlobalNamespace(state).
		beginNamespace("Aegis").
		beginNamespace("NativeComponents").
			addFunction("CreateRigidbody", CreateRigidbody).
				deriveClass<RigidbodyComponent, AegisComponent>("Rigidbody").
					addProperty("position", &RigidbodyComponent::GetPosition, &RigidbodyComponent::SetPosition).
					addFunction("AddForce", &RigidbodyComponent::AddForce).
					addFunction("GetForce", &RigidbodyComponent::GetForce).
					addFunction("AccelerateTo", &RigidbodyComponent::AccelerateTo).
					addFunction("AddTorque", &RigidbodyComponent::AddTorque).
					addFunction("AddForceForward", &RigidbodyComponent::AddForceForward).
					addFunction("changeGravity", &RigidbodyComponent::changeGravity).
					addProperty("isActive", &RigidbodyComponent::isActive).
				endClass().
			endNamespace().
		endNamespace();
}

void RigidbodyComponent::changeGravity(Vector3 acc)
{
	rigidbody->changeGravity(acc);
}
