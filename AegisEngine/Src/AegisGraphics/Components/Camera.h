#pragma once

#ifndef CAMERA_H
#define CAMERA_H

#include <OgreCamera.h>
class AegisCamera
{
public:
	AegisCamera(std::string camName,Ogre::SceneNode* node, bool maincam = true);
	~AegisCamera();

	Ogre::Matrix4 getProjectionMatrix();
	Ogre::Matrix4  getViewMatrix();

	void setViewport(double left, double top, double w, double h);
	Ogre::Viewport* getViewport();

	void setClipDistances(double near, double far);
	Ogre::Camera* GetCamera();
	Ogre::SceneNode* GetNode();

private:
	Ogre::Camera* mCamera_;
	Ogre::SceneManager* mngr;
	Ogre::SceneNode* mNode_;
	bool isMainCam_;
};

# endif