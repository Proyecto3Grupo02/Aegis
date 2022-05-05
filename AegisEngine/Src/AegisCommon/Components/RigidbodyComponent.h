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
	virtual void lateUpdate(float deltaTime) override;
	virtual void fixedUpdate() override;
	void SyncToTransform();
	void SetIterator(std::list<RigidbodyComponent*>::iterator physicsEntityIt);

	//GETS-------------------------------------------
	bool isActive() const;
	Vector3 GetPosition() const;
	//Vector4 getRotation();
	Vector3 GetForce() const;

	//SETS------------------------------------------
	void SetPosition(Vector3 pos);
	void SetRotationEuler(Vector3 rot);

	//FORCES----------------------------------------
	void AddForce(Vector3 force);
	Vector3 AccelerateTo(Vector3 targetVelocity, float maxAcceleration = 1000000000000);
	void AddTorque(Vector3 torque);
	void AddForceForward(float force);

	//FREEZE ROT------------------------------------
	void FreezeRot(bool _x, bool _y, bool _z);

	//GRAVITY---------------------------------------
	bool GetGravity()const;
	void SetGravity(bool g_);

	//LUA------------
	static void ConvertToLua(lua_State* state);

private:
	Vector3 initialPos;
	RigidBody* rigidbody = nullptr;
	Transform* transform = nullptr;
	std::list<RigidbodyComponent*>::iterator physicsEntityIt;
};

#endif // ! RIGIDBODY_H