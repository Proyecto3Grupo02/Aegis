#include "RigidbodyComponent.h"

#include "Entity.h"
#include <Scene.h>
#include "GameLoopData.h"
#include "MathUtils.h"

RigidbodyComponent::RigidbodyComponent(Entity* ent, std::string bodyMeshName, float m, bool useG, bool isK, bool isT,float scale)
	: AegisComponent("Rigidbody", ent)
{
	transform = ent->GetTransform();
	initialPos = transform->GetPosition();
	
	auto rot = transform->GetRotation();
	Vector4 rotVec(rot.x, rot.y, rot.z, rot.w);
	rigidbody = new RigidBody(bodyMeshName, transform->GetPosition(), transform->GetScale()*scale, rotVec,this, m, useG, isK,isT);
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

Vector3 RigidbodyComponent::AccelerateToRand()
{
	Vector3 vec(rand() % 10, 0 ,rand() % 10);
	return rigidbody->AccelerateTo(vec, Time()->deltaTime, 100000000000);
	rigidbody->setLinearVelocity();
}

void RigidbodyComponent::AddForceForward(float force) {
	Vector3 rot = transform->GetForward();
	AddForce(rot * force);
}

void RigidbodyComponent::ResetForce()
{
	rigidbody->clearForces();
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

void RigidbodyComponent::SetRotationEuler(Vector3 rot) {
	Vector4 eulerRot = MathUtils::EulerToVec4(rot);
	rigidbody->setRbRotation(eulerRot);
}

//FREEZE ROT------------------------------------------------------------------------------------------------
void RigidbodyComponent::FreezeRot (bool _x, bool _y, bool _z) {
	rigidbody->setFreezeRotation(_x, _y, _z);
}

//GRAVITY----------------------------------------------------------------------------------------------------
bool RigidbodyComponent::GetUsingGravity()const {
	return rigidbody->getUseGravity();
}

void RigidbodyComponent::SetUsingGravity(bool g_) {
	rigidbody->setUsingGravity(g_);
}



//LUA-------------------------------------------------------------------------------------------------------
RigidbodyComponent* CreateRigidbody(Entity* ent, LuaRef args) //Doesn't belong to this class
{
	std::string bodyName = ent->getName();
	float mass = LuaMngr()->ParseFloat(args["mass"], 1);
	bool useGravity = LuaMngr()->ParseBool(args["useGravity"], true);
	bool isKinematic = LuaMngr()->ParseBool(args["isKinematic"], false);
	bool isTrigger = LuaMngr()->ParseBool(args["isTrigger"], false);
	float scale = LuaMngr()->ParseFloat(args["scale"], 1);
	return new RigidbodyComponent(ent, bodyName, mass, useGravity, isKinematic,isTrigger,scale);
}

void RigidbodyComponent::enableCollision(bool enable_) {
	if (enable_)
	{
		rigidbody->enableCol();
	}
	else rigidbody->disableCol();
}

void RigidbodyComponent::ConvertToLua(lua_State* state)
{
	getGlobalNamespace(state).
		beginNamespace("Aegis").
		beginNamespace("NativeComponents").
			addFunction("CreateRigidbody", CreateRigidbody).
				deriveClass<RigidbodyComponent, AegisComponent>("Rigidbody").
					addProperty("position", &RigidbodyComponent::GetPosition, &RigidbodyComponent::SetPosition).
					addProperty("useGravity", &RigidbodyComponent::GetUsingGravity, &RigidbodyComponent::SetUsingGravity).
					addFunction("AddForce", &RigidbodyComponent::AddForce).
					addFunction("GetForce", &RigidbodyComponent::GetForce).
					addFunction("ClearForce", &RigidbodyComponent::ResetForce).
					addFunction("AccelerateTo", &RigidbodyComponent::AccelerateTo).
					addFunction("AccelerateToRand", &RigidbodyComponent::AccelerateToRand).
					addFunction("AddTorque", &RigidbodyComponent::AddTorque).
					addFunction("AddForceForward", &RigidbodyComponent::AddForceForward).
					addFunction("ChangeGravity", &RigidbodyComponent::changeGravity).
					addFunction("RayCastWorld", &RigidbodyComponent::Raycast).
					addFunction("SetRotationEuler", &RigidbodyComponent::SetRotationEuler).
					addFunction("SetAngular", &RigidbodyComponent::SetAngular).
					addFunction("FreezeRot", &RigidbodyComponent::FreezeRot).
					addProperty("isActive", &RigidbodyComponent::isActive).
					addFunction("EnableCol", &RigidbodyComponent::enableCollision).
					
				endClass().
			endNamespace().
		endNamespace();
}

void RigidbodyComponent::changeGravity(Vector3 acc)
{
	rigidbody->changeGravity(acc);
}

int RigidbodyComponent::Raycast(Vector3 origin, Vector3& dir, float distance)
{
	dir = origin + dir.getNormalized() * distance;
	return rigidbody->RayCast(origin, dir);
}
