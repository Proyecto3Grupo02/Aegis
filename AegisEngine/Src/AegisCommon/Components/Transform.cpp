#include "Transform.h"

#include "Entity.h"
#include "MathUtils.h"

using namespace MathUtils;

Vector3 Transform::getPosition() const
{
	return position;
}

Ogre::Quaternion Transform::getRotation() const
{
	return rotation;
}

Vector3 Transform::getScale() const
{
	return scale;
}

void Transform::setParent(Entity* ent)
{
	auto root = mNode->getCreator()->getRootSceneNode();
	auto oldParent = parentNode;
	auto oldParentEntity = parentEntity;
	parentNode = ent == nullptr ? root : ent->getNode();
	parentEntity = ent;
	
	if (oldParentEntity != ent && oldParentEntity != nullptr)
	{
		oldParentEntity->getTransform()->removeChild(getEntity());
		oldParentEntity->removeChild(getEntity());
	}

	if (parentEntity != nullptr)
	{
		parentEntity->getTransform()->addChild(this->getEntity());
		parentEntity->addChild(this->getEntity());
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

void Transform::setPosition(Vector3 newPos) {
	position = newPos;
}

void Transform::setRotation(Ogre::Quaternion newRot)
{
	rotation = newRot;
}

Vector3 Transform::getRotationEuler() const
{
	return OgreQuatEuler(rotation);
}

void Transform::setRotationEuler(Vector3 newRot)
{
	rotation = EulerToOgreQuat(newRot);
}

void Transform::setScale(Vector3 newScale)
{
	scale = newScale;
}

Vector3 Transform::getForward() const
{
	return RotateQuaternion(rotation, Vector3(0, 0, 1));
}

Vector3 Transform::getRight() const
{
	return RotateQuaternion(rotation, Vector3(1, 0, 0));
}

Vector3 Transform::getUp() const
{
	return RotateQuaternion(rotation, Vector3(0, 1, 0));
}

void Transform::yaw(float degrees)
{
	mNode->yaw(Ogre::Degree(degrees));
	rotation = mNode->getOrientation();
}

void Transform::pitch(float degrees)
{
	mNode->pitch(Ogre::Degree(degrees));
	rotation = mNode->getOrientation();
}

void Transform::roll(float degrees)
{
	mNode->roll(Ogre::Degree(degrees));
	rotation = mNode->getOrientation();
}

Transform::~Transform() {
	/*for (Entity* child : childs)
		delete child;*/
}

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
		addProperty("position", &Transform::getPosition, &Transform::setPosition).
		addProperty("scale", &Transform::getScale, &Transform::setScale).
		addProperty("rotation", &Transform::getRotation, &Transform::setRotation).
		addProperty("localEulerAngles", &Transform::getRotationEuler, &Transform::setRotationEuler).
		addFunction("SetParent", &Transform::setParent).
		addProperty("forward", &Transform::getForward, &Transform::setFoo).
		addProperty("right", &Transform::getRight, &Transform::setFoo).
		addProperty("up", &Transform::getUp, &Transform::setFoo).
		addFunction("Yaw", &Transform::yaw).
		addFunction("Pitch", &Transform::pitch).
		addFunction("Roll", &Transform::roll).
		endClass().
		endNamespace().
		endNamespace();
}

void Transform::addChild(Entity* child)
{
	childs.push_back(child);
}

void Transform::removeChild(Entity* child)
{
	childs.remove(child);
}

void Transform::destroyChilds()
{
	//Destroys every child calling its Destroy function
	for (Entity* child : childs)
		child->destroy();
}

