#pragma once


#include "btBulletDynamicsCommon.h"
#include "Vector3.h"
#include <functional>

class PhysicsMain;

class MotionState : public btMotionState
{
protected:
public:
	MotionState(const Vector3& offset = { 0,0,0 });
	~MotionState();

	// Methods from bullet physics

	virtual void getWorldTransform(Vector3 pos, Vector3 rot, btTransform& worldTrans) const;
	virtual void setWorldTransform(const btTransform& worldTrans, std::function<void(Vector3)> SetPosition);
};

