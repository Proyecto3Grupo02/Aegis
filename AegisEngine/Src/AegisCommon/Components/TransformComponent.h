#pragma once
#ifndef TRANSFORM_H 
#define TRANSFORM_H

#include "AegisComponent.h"
#include "Vector4.h"
#include "ILuaObject.h"

class Entity;

class TransformComponent : public AegisComponent, public ILuaObject {
public:
	TransformComponent(Ogre::SceneNode* node, Entity* ent) : AegisComponent("Transform", ent), position(Vector3()), rotation(Ogre::Quaternion()), scale(Vector3(1.0f, 1.0f, 1.0f)), mNode(node), parentNode(node->getParentSceneNode()), parentEntity(nullptr) {
		setDataAsInnerType(this);
		//ComponentManager::getInstance()->RegisterComponent<Transform>("Transform");
	};
	TransformComponent( Vector3 _pos, Ogre::Quaternion _rot, Vector3 _scale, Ogre::SceneNode* node, Entity* ent) :
			AegisComponent("Transform", ent), position(_pos), rotation(_rot), scale(_scale), mNode(node), parentNode(node->getParentSceneNode()), parentEntity(nullptr) {
		setDataAsInnerType(this);
		//ComponentManager::getInstance()->RegisterComponent<Transform>("Transform");
	};
	virtual ~TransformComponent();
	virtual void init() override {}
	virtual void update(float deltaTime) override;
	virtual void render() override;
	Vector3 getPosition() const;
	Ogre::Quaternion getRotation() const;
	Vector3 getRotationEuler() const;
	Vector3 getScale() const;

	void setParent(Entity* ent);

	void setPosition(Vector3 newPos);
	void setRotation(Ogre::Quaternion newRot);
	void setRotationEuler(Vector3 newRot);
	void setScale(Vector3 newScale);

	Vector3 getForward() const;
	Vector3 getRight() const;
	Vector3 getUp() const;

	void yaw(float degrees);
	void pitch(float degrees);
	void roll(float degrees);

	// It does nothing, it's for faking the setter
	void setFoo(Vector3 nothign) {};

	static void ConvertToLua(lua_State* state);

	void addChild(Entity* child);
	void removeChild(Entity* child);
	void destroyChilds();

protected:
	Ogre::SceneNode* mNode;
	Vector3 position;
	Ogre::Quaternion rotation;
	Vector3 scale;
	Ogre::SceneNode* parentNode;
	Entity* parentEntity;

private:
	std::list<Entity*> childs;
};

#endif //TRANSFORM