#include "RigidbodyComponent.h"

#include "Entity.h"
#include <Scene.h>


RigidbodyComponent::RigidbodyComponent(Entity* ent, std::string bodyMeshName, float m, bool useG, bool isK)
	: AegisComponent("Rigidbody", ent)
{
	transform = ent->GetTransform();
	initialPos = transform->GetPosition();
	rigidbody = new RigidBody(bodyMeshName, transform->GetPosition(), transform->GetScale(), m, useG, isK);
	mEntity_->getScene()->AddPhysicsEntity(this);

	SetDataAsInnerType(this);
}

RigidbodyComponent::~RigidbodyComponent()
{
	delete rigidbody;
	mEntity_->getScene()->RemovePhysicsEntity(this->physicsEntityIt);
};

void RigidbodyComponent::SyncToTransform()
{
	Vector3 updatedPos = rigidbody->getRbPosition();

	transform->SetPosition(rigidbody->getRbPosition());
	auto quat = rigidbody->getRotation();
	Ogre::Quaternion ogreQuat(quat.w, quat.x, quat.y, quat.z);
	transform->SetRotation(ogreQuat);
}

void RigidbodyComponent::SetIterator(std::list<RigidbodyComponent*>::iterator physicsEntityIt)
{
	this->physicsEntityIt = physicsEntityIt;
}

void RigidbodyComponent::AddForce(Vector3 force) {
	rigidbody->addForce(force);
}

Vector3 RigidbodyComponent::GetPosition() const{
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
		endClass().
		endNamespace().
		endNamespace();
}
