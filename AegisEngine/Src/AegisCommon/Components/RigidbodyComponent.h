#pragma once

#ifndef RIGIDBODY_COMPONENT_H
#define RIGIDBODY_COMPONENT_H

#include <string>
#include "AegisComponent.h"
#include "ILuaObject.h"
#include "Rigidbody.h"
#include "TransformComponent.h"

class Entity;

class RigidbodyComponent : public AegisComponent, public ILuaObject
{
public:
	RigidbodyComponent(Entity* ent, std::string bodyMeshName, float m = 1, bool useG = true, bool isK = false,bool isT =false,float scale = 1, float damp = 0);
	virtual ~RigidbodyComponent();

	virtual void init() override {};
	virtual void update(float deltaTime) override {};
	virtual void lateUpdate(float deltaTime) override;
	virtual void fixedUpdate() override;
	void syncTransformToRigidbody();
	void syncRigidbodyToTransform();
	void setIterator(std::list<RigidbodyComponent*>::iterator physicsEntityIt);

	//GETS-------------------------------------------
	bool isActive() const;
	Vector3 getPosition() const;
	//Vector4 getRotation();
	Vector3 getForce() const;
	bool getTrigger() const;
	float getDamping() const;

	//SETS------------------------------------------
	void setPosition(Vector3 pos);
	void setRotationEuler(Vector3 rot);
	void setTrigger(bool trig);
	void setAngular();
	void setDamping(float damp);

	//FORCES----------------------------------------
	void addForce(Vector3 force);
	Vector3 accelerateTo(Vector3 targetVelocity, float maxAcceleration = 1000000000000);
	Vector3 accelerateToRand();
	void addTorque(Vector3 torque);
	void addForceForward(float force);

	void resetVelocity();


	void resetForce();

	//FREEZE ROT------------------------------------
	void freezeRot(bool _x, bool _y, bool _z);

	//GRAVITY---------------------------------------
	bool getUsingGravity()const;
	void setUsingGravity(bool g_);

	//LUA------------
	static void ConvertToLua(lua_State* state);
	void changeGravity(Vector3 acc);
	int raycast(Vector3 origin, Vector3 &dest, float distance);
	friend class PhysicsSystem;

	//Activar o desactivar collider
	void enableCollision(bool enable_);

private:
	
	Vector3 initialPos;
	RigidBody* rigidbody = nullptr;
	TransformComponent* transform = nullptr;
	std::list<RigidbodyComponent*>::iterator physicsEntityIt;

	int cooldown = 3000;
};

#endif // ! RIGIDBODY_H