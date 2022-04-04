#pragma once
#include <OgreCamera.h>
class AegisCamera
{
public:
	AegisCamera();
	~AegisCamera();

private:
	Ogre::Camera* mCamera_;
	bool isMainCam_;

};

AegisCamera::AegisCamera()
{
}

AegisCamera::~AegisCamera()
{
}