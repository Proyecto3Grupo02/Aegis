#pragma once


#include "btBulletDynamicsCommon.h"
#include "Vector3.h"

class PhysicsMain;
class Transform;


class MotionState : public btMotionState
{
protected:
	Transform* transform;
	//Vector3 offset;
public:
	MotionState(Transform* transform, const Vector3& offset = { 0,0,0 });
	~MotionState();

	Transform* getTransform() const;

	//void setOffset(const Vector3& offset);
	// Methods from bullet physics

	virtual void getWorldTransform(btTransform& worldTrans) const;
	virtual void setWorldTransform(const btTransform& worldTrans);
};

