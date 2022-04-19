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

class RigidBody {
public:
	enum RigidBodyType { Box, Sphere, CapsuleX, CapsuleZ, Custom };

	RigidBody(std::string bodyMeshName, Vector3 pos, Vector3 scale, float m = 1, bool useG = true, bool isK = false);
	void init();
	~RigidBody() { };
	//void fixedUpdate();

	void addForce(Vector3 vec);

	bool getKinematic();
	bool getUseGravity();
	void setKinematic(bool sK);
	void setUsingGravity(bool uG);
	void setGravity(Vector3 vec);

	Vector3 getRbPosition();
	Vector4 getRotation();

	void setFreezeRotation(bool _x, bool _y, bool _z);

protected:
	btRigidBody* rigidBody;

	float mass;
	bool useGravity;
	bool isKinematic;
	std::vector<bool> freezePosition;
	std::vector<bool> freezeRotation;

	void createRigidBodyComponent(RigidBodyType rbType, Vector3 pos, Vector3 scale, std::string bodyMeshName = "", bool isConvex = true);
};

#endif // ! RIGIDBODY_H

