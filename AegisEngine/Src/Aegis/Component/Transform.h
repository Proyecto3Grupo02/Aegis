#pragma once



#include "AegisComponent.h"
#include "Vector4.h"
#include "ComponentManager.h"
class Entity;

class Transform : public AegisComponent {
public:
	Transform() : AegisComponent(), position(Vector3()), rotation(Vector4()), scale(Vector3(1.0f,1.0f,1.0f)) {
		ComponentManager::getInstance()->RegisterComponent<Transform>("Transform");
	};
	Transform( Vector3 _pos, Vector4 _rot, Vector3 _scale) :
			AegisComponent(), position(_pos), rotation(_rot), scale(_scale) {
		ComponentManager::getInstance()->RegisterComponent<Transform>("Transform");
	};
	virtual ~Transform() {}
	virtual void init(){}
	virtual void update();
	Vector3 GetPosition();
	Vector4 GetRotation();
	Vector3 GetScale();

	void SetPosition(Vector3 newPos);
	void SetRotation(Vector4 newRot);
	void SetScale(Vector3 newScale);

protected:
	Vector3 position;
	Vector4 rotation;
	Vector3 scale;
};