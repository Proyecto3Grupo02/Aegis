#pragma once

#ifndef RIGIDBODY_COMPONENT_H
#define RIGIDBODY_COMPONENT_H

#include <string>
#include "AegisComponent.h"
#include "../Interfaces/ILuaObject.h"
#include "../../AegisPhysics/Rigidbody.h"
#include "Transform.h"

class Entity;

class RigidbodyComponent : public AegisComponent, public ILuaObject
{
public:
	RigidbodyComponent(Entity* ent, std::string bodyMeshName, float m = 1, bool useG = true, bool isK = false);
	virtual ~RigidbodyComponent();

	virtual void init() override {};
	virtual void update(float deltaTime) override {};
	virtual void fixedUpdate() override {};
	void SyncToTransform();

	void SetIterator(std::list<RigidbodyComponent*>::iterator physicsEntityIt);

	//LUA------------
	static void ConvertToLua(lua_State* state);

private:
	Vector3 initialPos;
	RigidBody* rigidbody = nullptr;
	Transform* transform = nullptr;
	std::list<RigidbodyComponent*>::iterator physicsEntityIt;
};

#endif // ! RIGIDBODY_H