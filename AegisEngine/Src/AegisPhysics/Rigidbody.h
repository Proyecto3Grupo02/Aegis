#pragma once

#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include <vector>
#include <string>

class btRigidBody;
class btTransform;
class btQuaternion;
class Transform;
class Vector3;
class Vector4;
class RigidbodyComponent;

class RigidBody {
public:
	enum RigidBodyType { Box, Sphere, CapsuleX, CapsuleZ, Custom };

	RigidBody(std::string bodyMeshName, Vector3 pos, Vector3 scale, RigidbodyComponent* r, float m = 1, bool useG = true, bool isK = false);
	void init();
	~RigidBody();
	//void fixedUpdate();

	//GETS-------------------------------------
	bool isActive() const;
	bool getKinematic();
	bool getUseGravity();
	Vector3 getRbPosition();
	Vector3 getTotalForce();
	Vector4 getRotation();

	//SETS--------------------------------------
	void setActive(bool active = true);
	void setKinematic(bool sK);
	void setUsingGravity(bool uG);
	void setGravity(Vector3 vec);
	void setRbPosition(Vector3 vec);
	void setRbRotation(Vector4 vec);
	void setFreezeRotation(bool _x, bool _y, bool _z);

	//FORCES---------------------------------
	void addForce(Vector3 vec);
	void addTorque(Vector3 vec);
	void clearForces();

protected:
	btRigidBody* rigidBody;
	RigidbodyComponent* rbC;

	float mass;
	bool useGravity;
	bool isKinematic;
	std::vector<bool> freezePosition;
	std::vector<bool> freezeRotation;

	
	void createRigidBodyComponent(RigidBodyType rbType, Vector3 pos, Vector3 scale, std::string bodyMeshName = "", bool isConvex = true);
	friend class PhysicsSystem;

};

#endif // ! RIGIDBODY_H

