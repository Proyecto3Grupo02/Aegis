#include "Transform.h"

#include"RegisterComponent.h"
#include "Entity.h"


Vector3 Transform::GetPosition() const
{
	return position;
}

Quaternion Transform::GetRotation() const
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
	Vector3 newParentScale = ParseOgreVector3(parent->getScale());
	Vector3 newParentPos = ParseOgreVector3(parent->getPosition());

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
}

void Transform::SetPosition(Vector3 newPos) {
	position = newPos;
}

void Transform::SetRotation(Quaternion newRot)
{
	rotation = newRot;
}

Vector3 Transform::GetRotationEuler() const
{
	return rotation.GetEulerAngles();
}

void Transform::SetRotationEuler(Vector3 newRot)
{
	rotation = Quaternion::eulerToQuaternion(newRot);
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

void Transform::update(float deltaTime)
{
	UpdateOgreNode();
}

inline void Transform::UpdateOgreNode()
{
	mNode->setPosition(position.GetX(), position.GetY(), position.GetZ());
	mNode->setScale(scale.GetX(), scale.GetY(), scale.GetZ());
	mNode->setOrientation(rotation.GetW(), rotation.GetX(), rotation.GetY(), rotation.GetZ());
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

