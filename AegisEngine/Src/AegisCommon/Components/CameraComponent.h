#pragma once 

#ifndef CAMERA_H
#define CAMERA_H

#include "AegisComponent.h"
#include "../Utils/Quaternion.h"

class CameraComponent: 
	public AegisComponent
{
public:
	CameraComponent();
	~CameraComponent();
	
	void lookAt(const Vector3& dir);
	Vector3 getDirection() const;
	Quaternion getOrientation() const;
	void setDirection(const Vector3& direction);
	void setOrientation(const Quaternion& orientation);

	Vector3 worldToScreen(const Vector3& worldPoint);
	Vector3 worldToScreenPixel(const Vector3& worldPoint);

	static void ConvertToLua(lua_State* state);

	void setClipDistances(double near, double far);

private:
	bool isMainCam_;

};

#endif // _CAMERA_H
