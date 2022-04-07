#pragma once
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
private:
	Ogre::Camera* mCamera_;
	Ogre::SceneManager* mngr;
	Ogre::SceneNode* mNode_;
	bool isMainCam_;

};
