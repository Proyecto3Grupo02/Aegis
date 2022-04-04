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
	//if parent node is not null, remove from parent, then attach to ent node
	auto root = mNode->getCreator()->getRootSceneNode();

	position = position + ParseOgreVector3(parent->getPosition());
	UpdateOgreNode();
	parent->removeChild(mNode);

	if (ent == nullptr)
	{
		parent = root;
		root->addChild(mNode);
	}
	else
	{
		parent = ent->getNode();
		position = position - ent->GetTransform()->GetPosition();
		//rotation = rotation + ent->GetTransform()->GetRotation();
		//scale = scale.divide(ent->GetTransform()->GetScale());
		UpdateOgreNode();

		auto entNode = ent->getNode();
		entNode->addChild(mNode);
	}

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

