#pragma once

#ifndef RIGIDBODY_COMPONENT_H
#define RIGIDBODY_COMPONENT_H

#include <string>
#include "AegisComponent.h"
#include "ILuaObject.h"
#include "Rigidbody.h"
#include "Transform.h"

class Entity;

class RigidbodyComponent : public AegisComponent, public ILuaObject
{
public:
	RigidbodyComponent(Entity* ent, std::string bodyMeshName, float m = 1, bool useG = true, bool isK = false,bool isT =false,float scale = 1);
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
	Vector3 AccelerateToRand();
	void AddTorque(Vector3 torque);
	void AddForceForward(float force);

	void SetAngular() { rigidbody->SetAngularFactor(); }
	void ResetForce();

	//FREEZE ROT------------------------------------
	void FreezeRot(bool _x, bool _y, bool _z);

	//GRAVITY---------------------------------------
	bool GetUsingGravity()const;
	void SetUsingGravity(bool g_);

	//LUA------------
	static void ConvertToLua(lua_State* state);
	void changeGravity(Vector3 acc);
	int Raycast(Vector3 origin, Vector3 &dest, float distance);
	friend class PhysicsSystem;

	//Activar o desactivar collider
	void enableCollision(bool enable_);

private:
	
	Vector3 initialPos;
	RigidBody* rigidbody = nullptr;
	Transform* transform = nullptr;
	std::list<RigidbodyComponent*>::iterator physicsEntityIt;

	int cooldown = 3000;
};

#endif // ! RIGIDBODY_H