#include "TransformComponent.h"

#include "Entity.h"
#include "MathUtils.h"

Vector3 TransformComponent::getPosition() const
{
	return position;
}

Ogre::Quaternion TransformComponent::getRotation() const
{
	return rotation;
}

Vector3 TransformComponent::getScale() const
{
	return scale;
}

void TransformComponent::setParent(Entity* ent)
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
	Vector3 oldParentScale = MathUtils::ParseOgreVector3(oldParent->getScale());
	Vector3 oldParentPos = MathUtils::ParseOgreVector3(oldParent->getPosition());
	Ogre::Quaternion oldParentRotation = oldParent->getOrientation();

	// New parent data (the one we have attached to)
	Vector3 newParentScale = MathUtils::ParseOgreVector3(parentNode->getScale());
	Vector3 newParentPos = MathUtils::ParseOgreVector3(parentNode->getPosition());
	Ogre::Quaternion newParentRotation = parentNode->getOrientation();

	//Correction rotation "before" unparenting
	rotation = oldParentRotation * rotation;
	position = position.scalarMult(oldParentScale);
	position = MathUtils::RotateVector3ByQuaternion(oldParentRotation, position);
	scale = scale.scalarMult(oldParentScale);
	position = position + oldParentPos;

	// Correct data for parenting (inverse order)
	position = position - newParentPos;
	scale = scale.divide(newParentScale);
	position = MathUtils::RotateVector3ByQuaternion(newParentRotation.Inverse(), position);
	position = position.divide(newParentScale);
	rotation = newParentRotation.Inverse() * rotation;
}

void TransformComponent::setPosition(Vector3 newPos) {
	position = newPos;
}

void TransformComponent::setRotation(Ogre::Quaternion newRot)
{
	rotation = newRot;
}

Vector3 TransformComponent::getRotationEuler() const
{
	return MathUtils::OgreQuatEuler(rotation);
}

void TransformComponent::setRotationEuler(Vector3 newRot)
{
	rotation = MathUtils::EulerToOgreQuat(newRot);
}

void TransformComponent::setScale(Vector3 newScale)
{
	scale = newScale;
}

Vector3 TransformComponent::getForward() const
{
	return MathUtils::RotateQuaternion(rotation, Vector3(0, 0, 1));
}

Vector3 TransformComponent::getRight() const
{
	return MathUtils::RotateQuaternion(rotation, Vector3(1, 0, 0));
}

Vector3 TransformComponent::getUp() const
{
	return MathUtils::RotateQuaternion(rotation, Vector3(0, 1, 0));
}

void TransformComponent::yaw(float degrees)
{
	mNode->yaw(Ogre::Degree(degrees));
	rotation = mNode->getOrientation();
}

void TransformComponent::pitch(float degrees)
{
	mNode->pitch(Ogre::Degree(degrees));
	rotation = mNode->getOrientation();
}

void TransformComponent::roll(float degrees)
{
	mNode->roll(Ogre::Degree(degrees));
	rotation = mNode->getOrientation();
}

TransformComponent::~TransformComponent() {
	/*for (Entity* child : childs)
		delete child;*/
}

void TransformComponent::update(float deltaTime) {}

void TransformComponent::render()
{
	mNode->setPosition(MathUtils::Vector3ToOgre(position));
	mNode->setScale(MathUtils::Vector3ToOgre(scale));
	mNode->setOrientation(rotation);
}

void TransformComponent::ConvertToLua(lua_State* state)
{
	getGlobalNamespace(state).
		beginNamespace("Aegis").
		beginNamespace("NativeComponents").
		beginClass<TransformComponent>("Transform").
		addProperty("position", &TransformComponent::getPosition, &TransformComponent::setPosition).
		addProperty("scale", &TransformComponent::getScale, &TransformComponent::setScale).
		addProperty("rotation", &TransformComponent::getRotation, &TransformComponent::setRotation).
		addProperty("localEulerAngles", &TransformComponent::getRotationEuler, &TransformComponent::setRotationEuler).
		addFunction("SetParent", &TransformComponent::setParent).
		addProperty("forward", &TransformComponent::getForward, &TransformComponent::setFoo).
		addProperty("right", &TransformComponent::getRight, &TransformComponent::setFoo).
		addProperty("up", &TransformComponent::getUp, &TransformComponent::setFoo).
		addFunction("Yaw", &TransformComponent::yaw).
		addFunction("Pitch", &TransformComponent::pitch).
		addFunction("Roll", &TransformComponent::roll).
		endClass().
		endNamespace().
		endNamespace();
}

void TransformComponent::addChild(Entity* child)
{
	childs.push_back(child);
}

void TransformComponent::removeChild(Entity* child)
{
	childs.remove(child);
}

void TransformComponent::destroyChilds()
{
	//Destroys every child calling its Destroy function
	for (Entity* child : childs)
		child->destroy();
}

