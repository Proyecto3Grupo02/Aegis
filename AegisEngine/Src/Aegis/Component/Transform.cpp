#include "Transform.h"
#include"RegisterComponent.h"

REGISTER_FACTORY(Transform);

Vector3<float> Transform::GetPosition()
{
	return position;
}

Vector3<float> Transform::GetRotation()
{
	return rotation;
}

Vector3<float> Transform::GetScale()
{
	return scale;
}

void Transform::SetPosition(Vector3<float> newPos)
{
	position = newPos;
}

void Transform::SetRotation(Vector4<float> newRot)
{
	rotation = newRot;
}

void Transform::SetScale(Vector3<float> newScale)
{
	scale = newScale;
}
