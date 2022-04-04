
#include "Camera.h"
#include <OgreSceneManager.h>


AegisCamera::AegisCamera(std::string camName,Ogre::SceneNode* node, Ogre::SceneManager* sceneMng, bool maincam): 
	mNode_(node), mngr(sceneMng)
{
	mCamera_ = mngr->createCamera(camName);
}

AegisCamera::~AegisCamera()
{
}

void AegisCamera::setDirection(float x, float y, float z)
{
}

void AegisCamera::setOrientation(float x, float y, float z, float w)
{
}

