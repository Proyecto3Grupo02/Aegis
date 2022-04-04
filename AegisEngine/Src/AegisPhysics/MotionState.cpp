#include "MotionState.h"
#include "PhysicsMain.h"

MotionState::MotionState(const Vector3& off)
{
	//offset = off;
}

MotionState::~MotionState()
{
}

//
//void MotionState::setOffset(const Vector3& off)
//{
//	offset = off;
//}

void MotionState::getWorldTransform(Vector3 pos, Vector3 rot, btTransform& worldTrans) const
{
	worldTrans = PhysicsSystem::getInstance()->parseToBulletTransform(pos, rot);

	worldTrans.setOrigin(worldTrans.getOrigin());
}

void MotionState::setWorldTransform(const btTransform& worldTrans, std::function<void(Vector3)> SetPosition)
{
	btScalar x, y, z;
	worldTrans.getRotation().getEulerZYX(z, y, x);
	Vector3 angle = { x / SIMD_RADS_PER_DEG, y / SIMD_RADS_PER_DEG, z / SIMD_RADS_PER_DEG };
	//transform->setWorldRotation(angle);

	//agregar metodo para hacer camvio de vector de bullet al normal
	btVector3 pos = worldTrans.getOrigin();

	//transform->SetPosition({ pos.x() , pos.y() , pos.z() });
	SetPosition({ pos.x() , pos.y() , pos.z() });
}

