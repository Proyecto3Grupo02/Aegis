#pragma once 

#ifndef CAMERA_COMPONENT_H
#define CAMERA_COMPONENT_H

#include "AegisComponent.h"
#include "AegisCamera.h"
#include "Vector3.h"

enum SpaceReference{LOCAL, PARENT, WORLD};

class CameraComponent: 	public AegisComponent
{
public:
	CameraComponent(Entity* ent, LuaRef args);
	CameraComponent(Entity* ent, AegisCamera* cam);
	~CameraComponent();	

	Vector3 worldToScreen(const Vector3& worldPoint);
	Vector3 worldToScreenPixel(const Vector3& worldPoint);

	void setViewportDimensions(float left, float top, float width, float height);
	void setClipDistances(double near, double far);

	static void ConvertToLua(lua_State* state);

private:
	bool isMainCam_;
	AegisCamera* mCamera_;
};

#endif // _CAMERA_H
