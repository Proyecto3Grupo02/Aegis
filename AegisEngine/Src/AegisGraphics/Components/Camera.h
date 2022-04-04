#pragma once
#include <OgreCamera.h>
class AegisCamera
{
public:
	AegisCamera(std::string camName,Ogre::SceneNode* node, Ogre::SceneManager* sceneMng, bool maincam);
	~AegisCamera();

	void setDirection(float x, float y, float z);
	void setOrientation(float x, float y, float z, float w);

private:
	Ogre::Camera* mCamera_;
	Ogre::SceneManager* mngr;
	Ogre::SceneNode* mNode_;
	bool isMainCam_;

};
