#pragma once 

#ifndef CAMERA_H
#define CAMERA_H

#include "AegisComponent.h"
#include "../Utils/Quaternion.h"
#include "../../AegisGraphics/Components/Camera.h"
#include "Transform.h"

enum SpaceReference{LOCAL, PARENT, WORLD};

class CameraComponent: 
	public AegisComponent
{
public:
	CameraComponent(Entity* ent, std::string name,bool isMainCam);
	~CameraComponent();
	
	void lookAt(float x, float y, float z,SpaceReference mRef );
	Vector3 getDirection() const;
	Quaternion getOrientation() const;
	void setDirection(Vector3 dir);
	void setOrientation(const Quaternion& orientation);

	Vector3 worldToScreen(const Vector3& worldPoint);
	Vector3 worldToScreenPixel(const Vector3& worldPoint);

	void setViewportDimensions(float left, float top, float width, float height);
	static void ConvertToLua(lua_State* state);

	void setClipDistances(double near, double far);

private:
	bool isMainCam_;
	AegisCamera* mCamera_;
	Ogre::SceneNode* mNode_;
	Transform* tr_;

	Vector3 mDirection_;
	Quaternion mOrientation_;
};

#endif // _CAMERA_H
