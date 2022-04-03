#include "MotionState.h"
#include "PhysicsMain.h"
#include "Transform.h"

MotionState::MotionState(Transform* transform, const Vector3& off) : transform(transform)
{
	//offset = off;
}

MotionState::~MotionState()
{
}

Transform* MotionState::getTransform() const
{
	return transform;
}
//
//void MotionState::setOffset(const Vector3& off)
//{
//	offset = off;
//}

void MotionState::getWorldTransform(btTransform& worldTrans) const
{
	worldTrans = PhysicsSystem::getInstance()->parseToBulletTransform(transform);

	worldTrans.setOrigin(worldTrans.getOrigin());
}

void MotionState::setWorldTransform(const btTransform& worldTrans)
{
	btScalar x, y, z;
	worldTrans.getRotation().getEulerZYX(z, y, x);
	Vector3 angle = { x / SIMD_RADS_PER_DEG, y / SIMD_RADS_PER_DEG, z / SIMD_RADS_PER_DEG };
	//transform->setWorldRotation(angle);

	//agregar metodo para hacer camvio de vector de bullet al normal
	btVector3 pos = worldTrans.getOrigin();

	transform->SetPosition({ pos.x() , pos.y() , pos.z() });
}

