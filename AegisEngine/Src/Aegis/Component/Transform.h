#pragma once

#ifndef TRANSFORM_
#define TRANSFORM_
#include "Component.h"
#include "Vector4.h"

class Entity;

class Transform : public Component {
public:
	Transform(Entity* ent) : Component(ent), position(Vector3()), rotation(Vector4()), scale(Vector3()) {};
	Transform(Entity* ent, Vector3 _pos, Vector4 _rot, Vector3 _scale) :
			Component(ent), position(_pos), rotation(_rot), scale(_scale) {};

	Vector3 GetPosition();
	Vector3 GetRotation();
	Vector3 GetScale();

	void SetPosition(Vector3 newPos);
	void SetRotation(Vector4 newRot);
	void SetScale(Vector3 newScale);

protected:
	Vector3 position;
	Vector4 rotation;
	Vector3 scale;
};

#endif TRANSFORM_