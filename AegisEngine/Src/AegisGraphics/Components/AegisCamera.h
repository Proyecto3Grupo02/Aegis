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
	Ogre::Camera* getCamera();
	Ogre::SceneNode* getNode();

	void free();

private:
	Ogre::Camera* mCamera_ = nullptr;
	Ogre::SceneManager* mngr = nullptr;
	Ogre::SceneNode* mNode_ = nullptr;
	bool isMainCam_;

};

# endif