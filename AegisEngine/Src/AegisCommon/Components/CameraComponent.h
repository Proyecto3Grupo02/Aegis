#pragma once 

#ifndef CAMERA_H
#define CAMERA_H

#include "AegisComponent.h"
#include "../Utils/Quaternion.h"
#include "../../AegisGraphics/Components/Camera.h"

class CameraComponent: 
	public AegisComponent
{
public:
	CameraComponent(Entity* ent);
	~CameraComponent();
	
	void lookAt(const Vector3& dir);
	Vector3 getDirection() const;
	Quaternion getOrientation() const;
	void setDirection(Vector3 dir);
	void setOrientation(const Quaternion& orientation);

	Vector3 worldToScreen(const Vector3& worldPoint);
	Vector3 worldToScreenPixel(const Vector3& worldPoint);

	static void ConvertToLua(lua_State* state);

	void setClipDistances(double near, double far);

private:
	bool isMainCam_;
	AegisCamera* mCamera_;
	Ogre::SceneNode* mNode_;

	Vector3 mDirection_;
	Quaternion mOrientation_;
};

#endif // _CAMERA_H
