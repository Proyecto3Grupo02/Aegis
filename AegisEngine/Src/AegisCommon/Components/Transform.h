#pragma once
#ifndef TRANSFORM_H 
#define TRANSFORM_H

#include "AegisComponent.h"
#include "../Utils/Vector4.h"
#include "../Interfaces/ILuaObject.h"

class Entity;

class Transform : public AegisComponent, public ILuaObject {
public:
	Transform(Ogre::SceneNode* node, Entity* ent) : AegisComponent("Transform", ent), position(Vector3()), rotation(Ogre::Quaternion()), scale(Vector3(1.0f, 1.0f, 1.0f)), mNode(node), parentNode(node->getParentSceneNode()), parentEntity(nullptr) {
		SetDataAsInnerType(this);
		//ComponentManager::getInstance()->RegisterComponent<Transform>("Transform");
	};
	Transform( Vector3 _pos, Ogre::Quaternion _rot, Vector3 _scale, Ogre::SceneNode* node, Entity* ent) :
			AegisComponent("Transform", ent), position(_pos), rotation(_rot), scale(_scale), mNode(node), parentNode(node->getParentSceneNode()), parentEntity(nullptr) {
		SetDataAsInnerType(this);
		//ComponentManager::getInstance()->RegisterComponent<Transform>("Transform");
	};
	virtual ~Transform();
	virtual void init() override {}
	virtual void update(float deltaTime) override;
	virtual void render() override;
	Vector3 GetPosition() const;
	Ogre::Quaternion GetRotation() const;
	Vector3 GetRotationEuler() const;
	Vector3 GetScale() const;

	void SetParent(Entity* ent);

	void SetPosition(Vector3 newPos);
	void SetRotation(Ogre::Quaternion newRot);
	void SetRotationEuler(Vector3 newRot);
	void SetScale(Vector3 newScale);

	static void ConvertToLua(lua_State* state);

	void AddChild(Entity* child);
	void RemoveChild(Entity* child);
	void DestroyChilds();
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