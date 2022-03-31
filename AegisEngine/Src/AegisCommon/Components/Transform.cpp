#include "Transform.h"

#include"RegisterComponent.h"
#include "Entity.h"


Vector3 Transform::GetPosition() const
{
	return position;
}

Vector4 Transform::GetRotation()
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

void Transform::ConvertToLua(lua_State* state)
{
	getGlobalNamespace(state).
		beginNamespace("ECS").
			beginClass<Transform>("Transform").
			addProperty("position", &Transform::GetPosition, &Transform::SetPosition).
			endClass().
		endNamespace();
}

void Transform::update()
{
	//pass the parameters from vector3 /vector4 to Ogre::Node position rotation and scale
	getEntity()->getNode()->setPosition(position.GetX(), position.GetY(), position.GetZ());
	getEntity()->getNode()->setScale(scale.GetX(), scale.GetY(), scale.GetZ());
	getEntity()->getNode()->setOrientation(rotation.GetX(), rotation.GetY(), rotation.GetZ(), rotation.GetW());
}
