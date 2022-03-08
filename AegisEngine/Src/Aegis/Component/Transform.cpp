#include "Transform.h"
#include"RegisterComponent.h"

//REGISTER_FACTORY(Transform);

Vector3 Transform::GetPosition()
{
	return position;
}

Vector3 Transform::GetRotation()
{
	return rotation;
}

Vector3 Transform::GetScale()
{
	return scale;
}

void Transform::SetPosition(Vector3 newPos)
{
	position = newPos;
}

void Transform::SetRotation(Vector4 newRot)
{
	rotation = newRot;
}

void Transform::SetScale(Vector3 newScale)
{
	scale = newScale;
}
