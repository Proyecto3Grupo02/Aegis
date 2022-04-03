#pragma once

#ifndef RIGIDBODY_H
#define RIGIDBODY_H


#include "AegisComponent.h"
#include <vector>
#include <string>

class btRigidBody;
class Transform;
class Vector3;

class RigidBody : public AegisComponent {
public:
	enum RigidBodyType { Box, Sphere, CapsuleX, CapsuleZ, Custom };

	RigidBody(Entity* ent, std::string bodyMeshName, float m = 1, bool useG = true, bool isK = false);
	void init();
	~RigidBody() {};
	void fixedUpdate();

	void addForce(Vector3 vec);

	bool getKinematic();
	bool getUseGravity();
	void setKinematic(bool sK);
	void setUsingGravity(bool uG);
	void setGravity(Vector3 vec);

	void setFreezeRotation(bool _x, bool _y, bool _z);

protected:
	btRigidBody* rigidBody;
	float mass;
	bool useGravity;
	bool isKinematic;
	std::vector<bool> freezePosition;
	std::vector<bool> freezeRotation;
	Transform* transform;

	void createRigidBodyComponent(RigidBodyType rbType, std::string bodyMeshName = "", bool isConvex = true);
};

#endif // ! RIGIDBODY_H

