#pragma once
#include "Component.h"
#include "Vector4.h"

class Entity;

class Transform : public Component {
public:
	Transform(Entity* ent) : Component(ent), position(Vector3<float>()), rotation(Vector4<float>()), scale(Vector3<float>()) {};
	Transform(Entity* ent, Vector3<float> _pos, Vector4<float> _rot, Vector3<float> _scale) :
			Component(ent), position(_pos), rotation(_rot), scale(_scale) {};

	Vector3<float> GetPosition();
	Vector3<float> GetRotation();
	Vector3<float> GetScale();

	void SetPosition(Vector3 <float> newPos);
	void SetRotation(Vector4 <float> newRot);
	void SetScale(Vector3 <float> newScale);

protected:
	Vector3 <float> position;
	Vector4 <float> rotation;
	Vector3 <float> scale;
};