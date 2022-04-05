#include "Transform.h"

#include"RegisterComponent.h"
#include "Entity.h"
#include <OgreMatrix3.h>

Vector3 Transform::GetPosition() const
{
	return position;
}

Ogre::Quaternion Transform::GetRotation() const
{
	return rotation;
}



Vector3 Transform::GetScale() const
{
	return scale;
}

void Transform::SetParent(Entity* ent)
{
	auto root = mNode->getCreator()->getRootSceneNode();
	auto oldParent = parent;
	parent = ent == nullptr ? root : ent->getNode();

	Vector3 oldParentScale = ParseOgreVector3(oldParent->getScale());
	Vector3 oldParentPos = ParseOgreVector3(oldParent->getPosition());
	Ogre::Quaternion oldParentRotation = oldParent->getOrientation();
	Vector3 newParentScale = ParseOgreVector3(parent->getScale());
	Vector3 newParentPos = ParseOgreVector3(parent->getPosition());
	Ogre::Quaternion newParentRotation = parent->getOrientation();

	//Correction rotation before unparenting
	rotation = EulerToOgreQuat((GetRotationEuler() + OgreQuatEuler(oldParentRotation)));
	mNode->setOrientation(rotation);

	// Correct data for unparenting
	scale = scale.scalarMult(oldParentScale);
	position = position + oldParentPos;
	position = position.scalarMult(oldParentScale);

	// Correct data for parenting
	scale = scale.divide(newParentScale);
	position = position.divide(newParentScale);
	position = position - newParentPos;

	oldParent->removeChild(mNode);
	parent->addChild(mNode);
	UpdateOgreNode();

	// Correct 
	auto posAfterRotation = mNode->getPosition();
	//mNode->setPosition(Ogre::Vector3(0));
	rotation = EulerToOgreQuat((GetRotationEuler() - OgreQuatEuler(newParentRotation)));
	mNode->setOrientation(rotation);
	//mNode->translate(mNode->getPosition()-posAfterRotation);
	//position = ParseOgreVector3(mNode->getPosition());

}

Vector3 Transform::OgreQuatEuler(const Ogre::Quaternion& quaternion)
{
	Ogre::Matrix3 mx2;
	quaternion.ToRotationMatrix(mx2);
	Ogre::Radian x, y, z;
	mx2.ToEulerAnglesYXZ(y, x, z);
	Vector3 vect(x.valueAngleUnits(),
		y.valueAngleUnits(), z.valueAngleUnits());

	return vect;
}

Ogre::Quaternion Transform::EulerToOgreQuat(const Vector3& degreesVector)
{
	Ogre::Matrix3 mx;
	mx.FromEulerAnglesYXZ(Ogre::Degree(degreesVector.y), Ogre::Degree(degreesVector.x), Ogre::Degree(degreesVector.z));
	Ogre::Quaternion result(mx);
	return result;
}

void Transform::SetPosition(Vector3 newPos) {
	position = newPos;
}

void Transform::SetRotation(Ogre::Quaternion newRot)
{
	rotation = newRot;
}

Vector3 Transform::GetRotationEuler() const
{
	return OgreQuatEuler(rotation);
}

void Transform::SetRotationEuler(Vector3 newRot)
{
	//auto a = Ogre::Matrix3::FromEulerAnglesXYZ(Ogre::Radian(1), Ogre::Radian(1), Ogre::Radian(1));
	//rotation = Quaternion(Ogre::Euler(newRot.x, newRot.y, newRot.z));
	rotation = EulerToOgreQuat(newRot);
}

void Transform::SetScale(Vector3 newScale)
{
	scale = newScale;
}

Vector3 Transform::ParseOgreVector3(Ogre::Vector3 ogreVec)
{
	return Vector3(ogreVec.x, ogreVec.y, ogreVec.z);
}

Ogre::Vector3 Transform::Vector3ToOgre(Vector3 vec)
{
	return Ogre::Vector3(vec.x, vec.y, vec.z);
}

Quaternion Transform::ParseOgreQuaternion(Ogre::Quaternion quat)
{
	return Quaternion(quat.x, quat.y, quat.z, quat.z);
}


void Transform::update(float deltaTime)
{
	UpdateOgreNode();
}

inline void Transform::UpdateOgreNode()
{
	mNode->setPosition(position.GetX(), position.GetY(), position.GetZ());
	mNode->setScale(scale.GetX(), scale.GetY(), scale.GetZ());
	mNode->setOrientation(rotation);
}

void Transform::ConvertToLua(lua_State* state)
{
	getGlobalNamespace(state).
		beginNamespace("Aegis").
		beginNamespace("NativeComponents").
		beginClass<Transform>("Transform").
		addProperty("position", &Transform::GetPosition, &Transform::SetPosition).
		addProperty("scale", &Transform::GetScale, &Transform::SetScale).
		addProperty("rotation", &Transform::GetRotation, &Transform::SetRotation).
		addProperty("localEulerAngles", &Transform::GetRotationEuler, &Transform::SetRotationEuler).
		addFunction("SetParent", &Transform::SetParent).
		endClass().
		endNamespace().
		endNamespace();
}

