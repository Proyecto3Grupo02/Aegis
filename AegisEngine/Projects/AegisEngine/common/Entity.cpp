#include "Entity.h"

Entity::Entity()
{
}

Entity::~Entity()
{
}

void Entity::init()
{
}

void Entity::fixedUpdate()
{
}

void Entity::update()
{
}

void Entity::lateUpdate()
{
}

void Entity::render()
{
}

void Entity::addComponent(Component* component)
{
}

void Entity::removeComponent(Component* component)
{
}

Component* Entity::getComponent(unsigned int cmpID)
{
	return nullptr;
}

void Entity::receiveEvent(Entity* receive)
{
}

bool Entity::hasComponent(unsigned int cmpID)
{
	return false;
}

void Entity::onCollision(Entity* other)
{
}

void Entity::onTrigger(Entity* other)
{
}
	