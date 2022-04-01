#pragma once
#ifndef TRANSFORM_H 
#define TRANSFORM_H

#include "AegisComponent.h"
#include "../Utils/Vector4.h"
#include "../Managers/ComponentManager.h"
#include "../Interfaces/ILuaObject.h"

class Entity;

class Transform : public AegisComponent, public ILuaObject {
public:
	Transform() : AegisComponent(), position(Vector3()), rotation(Vector4()), scale(Vector3(1.0f,1.0f,1.0f)) {
		SetDataAsInnerType(this);
		SetComponentName("Transform");
		//ComponentManager::getInstance()->RegisterComponent<Transform>("Transform");
	};
	Transform( Vector3 _pos, Vector4 _rot, Vector3 _scale) :
			AegisComponent(), position(_pos), rotation(_rot), scale(_scale) {
		SetDataAsInnerType(this);
		SetComponentName("Transform");
		//ComponentManager::getInstance()->RegisterComponent<Transform>("Transform");
	};
	virtual ~Transform() {}
	virtual void init(){}
	virtual void update();
	Vector3 GetPosition() const;
	Vector4 GetRotation() const;
	Vector3 GetScale() const;

	void SetPosition(Vector3 newPos);
	void SetRotation(Vector4 newRot);
	void SetScale(Vector3 newScale);

	static void ConvertToLua(lua_State* state);
protected:
	Vector3 position;
	Vector4 rotation;
	Vector3 scale;
};

#endif //TRANSFORM