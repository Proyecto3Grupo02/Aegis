#include "Transform.h"

#include"RegisterComponent.h"
#include "Entity.h"
#include <OgreMatrix3.h>
#include "../Utils/MathUtils.h"

using namespace MathUtils;

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

	oldParent->removeChild(mNode);
	parent->addChild(mNode);

	// Old parent data (the one we have detached of)
	Vector3 oldParentScale = ParseOgreVector3(oldParent->getScale());
	Vector3 oldParentPos = ParseOgreVector3(oldParent->getPosition());
	Ogre::Quaternion oldParentRotation = oldParent->getOrientation();

	// New parent data (the one we have attached to)
	Vector3 newParentScale = ParseOgreVector3(parent->getScale());
	Vector3 newParentPos = ParseOgreVector3(parent->getPosition());
	Ogre::Quaternion newParentRotation = parent->getOrientation();

	//Correction rotation "before" unparenting
	rotation = EulerToOgreQuat((GetRotationEuler() + OgreQuatEuler(oldParentRotation)));
	position = position.scalarMult(oldParentScale);
	position = RotateByQuaternion(oldParentRotation, position);
	scale = scale.scalarMult(oldParentScale);
	position = position + oldParentPos;

	// Correct data for parenting (inverse order)
	position = position - newParentPos;
	scale = scale.divide(newParentScale);
	position = RotateByQuaternion(newParentRotation.Inverse(), position);
	position = position.divide(newParentScale);
	rotation = EulerToOgreQuat((GetRotationEuler() - OgreQuatEuler(newParentRotation)));
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
	rotation = EulerToOgreQuat(newRot);
}

void Transform::SetScale(Vector3 newScale)
{
	scale = newScale;
}

void Transform::update(float deltaTime) {}

void Transform::UpdateOgreNode()
{
	mNode->setPosition(Vector3ToOgre(position));
	mNode->setScale(Vector3ToOgre(scale));
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

