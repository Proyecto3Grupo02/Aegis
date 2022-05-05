#include "Transform.h"

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
	auto oldParent = parentNode;
	auto oldParentEntity = parentEntity;
	parentNode = ent == nullptr ? root : ent->getNode();
	parentEntity = ent;
	
	if (oldParentEntity != ent && oldParentEntity != nullptr)
	{
		oldParentEntity->GetTransform()->RemoveChild(GetEntity());
		oldParentEntity->RemoveChild(GetEntity());
	}

	if (parentEntity != nullptr)
	{
		parentEntity->GetTransform()->AddChild(this->GetEntity());
		parentEntity->AddChild(this->GetEntity());
	}

	oldParent->removeChild(mNode);
	parentNode->addChild(mNode);

	// Old parent data (the one we have detached of)
	Vector3 oldParentScale = ParseOgreVector3(oldParent->getScale());
	Vector3 oldParentPos = ParseOgreVector3(oldParent->getPosition());
	Ogre::Quaternion oldParentRotation = oldParent->getOrientation();

	// New parent data (the one we have attached to)
	Vector3 newParentScale = ParseOgreVector3(parentNode->getScale());
	Vector3 newParentPos = ParseOgreVector3(parentNode->getPosition());
	Ogre::Quaternion newParentRotation = parentNode->getOrientation();

	//Correction rotation "before" unparenting
	rotation = oldParentRotation * rotation;
	position = position.scalarMult(oldParentScale);
	position = RotateVector3ByQuaternion(oldParentRotation, position);
	scale = scale.scalarMult(oldParentScale);
	position = position + oldParentPos;

	// Correct data for parenting (inverse order)
	position = position - newParentPos;
	scale = scale.divide(newParentScale);
	position = RotateVector3ByQuaternion(newParentRotation.Inverse(), position);
	position = position.divide(newParentScale);
	rotation = newParentRotation.Inverse() * rotation;
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

Vector3 Transform::GetForward() const
{
	return RotateQuaternion(rotation, Vector3(0, 0, 1));
}

Vector3 Transform::GetRight() const
{
	return RotateQuaternion(rotation, Vector3(1, 0, 0));
}

Vector3 Transform::GetUp() const
{
	return RotateQuaternion(rotation, Vector3(0, 1, 0));
}

void Transform::Yaw(float degrees)
{
	mNode->yaw(Ogre::Degree(degrees));
	rotation = mNode->getOrientation();
}

void Transform::Pitch(float degrees)
{
	mNode->pitch(Ogre::Degree(degrees));
	rotation = mNode->getOrientation();
}

void Transform::Roll(float degrees)
{
	mNode->roll(Ogre::Degree(degrees));
	rotation = mNode->getOrientation();
}

Transform::~Transform() {}

void Transform::update(float deltaTime) {}

void Transform::render()
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
		addProperty("forward", &Transform::GetForward, &Transform::SetFoo).
		addProperty("right", &Transform::GetRight, &Transform::SetFoo).
		addProperty("up", &Transform::GetUp, &Transform::SetFoo).
		addFunction("Yaw", &Transform::Yaw).
		addFunction("Pitch", &Transform::Pitch).
		addFunction("Roll", &Transform::Roll).
		endClass().
		endNamespace().
		endNamespace();
}

void Transform::AddChild(Entity* child)
{
	childs.push_back(child);
}

void Transform::RemoveChild(Entity* child)
{
	childs.remove(child);
}

void Transform::DestroyChilds()
{
	//Destroys every child calling its Destroy function
	for (Entity* child : childs)
		child->Destroy();
}

