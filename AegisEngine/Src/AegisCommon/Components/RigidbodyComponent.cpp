#include "RigidbodyComponent.h"

#include "Entity.h"

RigidbodyComponent::RigidbodyComponent(Entity* ent, std::string bodyMeshName, float m = 1, bool useG = true, bool isK = false) 
	: AegisComponent("Rigidbody", ent) 
{
	Transform* t = ent->GetTransform();
	rigidbody = new RigidBody(bodyMeshName, t->GetPosition(), t->GetScale(), m, useG, isK);
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
