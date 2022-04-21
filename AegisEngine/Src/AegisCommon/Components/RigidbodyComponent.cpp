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
}

RigidbodyComponent::~RigidbodyComponent()
{
	delete rigidbody;
	mEntity_->getScene()->RemovePhysicsEntity(this->physicsEntityIt);
};

//LUA-------------------------------------------------------------------------------------------------------
RigidbodyComponent* CreateRigidbody(Entity* ent, LuaRef args) //Doesn't belong to this class
{
	std::string bodyName = LuaMngr()->ParseString(args["bodyName"], "DefaultBodyName");
	float mass = LuaMngr()->ParseFloat(args["mass"], 1);
	bool useGravity = LuaMngr()->ParseBool(args["useGravity"], true);
	bool isKinematic = LuaMngr()->ParseBool(args["isKinematic"], false);

	return new RigidbodyComponent(ent, bodyName, mass, useGravity, isKinematic);
}

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

void RigidbodyComponent::ConvertToLua(lua_State* state)
{
	getGlobalNamespace(state).
		beginNamespace("Aegis").
			beginNamespace("NativeComponents").
				addFunction("CreateRigidbody", CreateRigidbody).
				deriveClass<RigidbodyComponent, AegisComponent>("Rigidbody").
				endClass().
			endNamespace().
		endNamespace();
}
