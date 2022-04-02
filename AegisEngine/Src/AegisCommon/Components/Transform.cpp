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

void Transform::SetPosition(Vector3 newPos)
{
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

void Transform::update(float deltaTime)
{
	//pass the parameters from vector3 /vector4 to Ogre::Node position rotation and scale
	mNode->setPosition(position.GetX(), position.GetY(), position.GetZ());
	mNode->setScale(scale.GetX(), scale.GetY(), scale.GetZ());
	mNode->setOrientation(rotation.GetW(),rotation.GetX(), rotation.GetY(), rotation.GetZ());
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
		endClass().
		endNamespace().
		endNamespace();
}

